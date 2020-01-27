/////////////////////////////////////////////////////////////////////
// Class implementation file for MSTW PDFs.
// Original C++ version by Jeppe Andersen.
// Modified by Graeme Watt <Graeme.Watt(at)cern.ch>.
// Updated 25/06/2010: Enlarge allowed range for m_c and m_b.
// Updated 25/01/2011: Fix "nan" bug for q <= m_c when m_c^2 < 1.25 GeV^2.
//
// Usage:
// Initialising an instance of the class:
//   c_mstwpdf pdf("filename.dat")
// with "filename.dat" being the data file to interpolate.
//
// A call to the method 
//   c_mstwpdf::update(x,q)
// updates the parton content to the values at (x,q^2).
// The parton contents can then be accessed in
//   c_mstwpdf::cont.upv etc.
// This method is faster if all the flavours need to be evaluated.
//
// A call to the method 
//   c_mstwpdf::parton(f,x,q)
// will return the value of the PDF with flavour 'f' at (x,q^2).
// Now use PDG notation for parton flavour (apart from gluon=0, not 21):
//  f =   -6,  -5,  -4,  -3,  -2,  -1,0,1,2,3,4,5,6
//    = tbar,bbar,cbar,sbar,ubar,dbar,g,d,u,s,c,b,t.
// Can also get valence quarks directly:
//  f =  7, 8, 9,10,11,12.
//    = dv,uv,sv,cv,bv,tv.
// Photon: f = 13.
// This method is fastest if only one flavour needs to be evaluated.
/////////////////////////////////////////////////////////////////////

#include "mstwpdf.h"

int locate(double xx[],int n,double x)
  // returns an integer j such that x lies inbetween xx[j] and xx[j+1].
  // unit offset of increasing ordered array xx assumed.
  // n is the length of the array (xx[n] highest element).
{
  int ju,jm,jl(0),j;
  ju=n+1;
  
  while (ju-jl>1) {
    jm=(ju+jl)/2; // compute a mid point.
    if ( x>= xx[jm])
      jl=jm;
    else ju=jm;
  }
  if (x==xx[1]) j=1;
  else if (x==xx[n]) j=n-1;
  else j=jl;
  
  return j;
}

double polderivative1(double x1,double x2,double x3,double y1,double y2,double y3)
  // returns the estimate of the derivative at x1 obtained by a polynomial 
  // interpolation using the three points (x_i,y_i).
{
  return (x3*x3*(y1-y2)+2.0*x1*(x3*(-y1+y2)+x2*(y1-y3))+x2*x2*(-y1+y3)+x1*x1*(-y2+y3))/((x1-x2)*(x1-x3)*(x2-x3));
}

double polderivative2(double x1,double x2,double x3,double y1,double y2,double y3)
  // returns the estimate of the derivative at x2 obtained by a polynomial 
  // interpolation using the three points (x_i,y_i).
{
  return (x3*x3*(y1-y2)-2.0*x2*(x3*(y1-y2)+x1*(y2-y3))+x2*x2*(y1-y3)+x1*x1*(y2-y3))/((x1-x2)*(x1-x3)*(x2-x3));
}

double polderivative3(double x1,double x2,double x3,double y1,double y2,double y3)
  // returns the estimate of the derivative at x3 obtained by a polynomial 
  // interpolation using the three points (x_i,y_i).
{
  return (x3*x3*(-y1+y2)+2.0*x2*x3*(y1-y3)+x1*x1*(y2-y3)+x2*x2*(-y1+y3)+2.0*x1*x3*(-y2+y3))/((x1-x2)*(x1-x3)*(x2-x3));
}

double c_mstwpdf::xx[nx+1];

double c_mstwpdf::qq[nq+1];

c_mstwpdf::c_mstwpdf(string filename,bool warn_in,bool fatal_in)
  // The constructor: this will initialise the functions automatically.
{
  int i,n,m,k,l,j; // counters
  double dtemp;

  // Variables used for initialising c_ij array:
  double f[np+1][nx+1][nq+1];
  double f1[np+1][nx+1][nq+1]; // derivative w.r.t. x
  double f2[np+1][nx+1][nq+1]; // derivative w.r.t. q
  double f12[np+1][nx+1][nq+1];// cross derivative
  double f21[np+1][nx+1][nq+1];// cross derivative

  int wt[16][16]={{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		  {-3,0,0,3,0,0,0,0,-2,0,0,-1,0,0,0,0},
		  {2,0,0,-2,0,0,0,0,1,0,0,1,0,0,0,0},
		  {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
		  {0,0,0,0,-3,0,0,3,0,0,0,0,-2,0,0,-1},
		  {0,0,0,0,2,0,0,-2,0,0,0,0,1,0,0,1},
		  {-3,3,0,0,-2,-1,0,0,0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0,-3,3,0,0,-2,-1,0,0},
		  {9,-9,9,-9,6,3,-3,-6,6,-6,-3,3,4,2,1,2},
		  {-6,6,-6,6,-4,-2,2,4,-3,3,3,-3,-2,-1,-1,-2},
		  {2,-2,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0,2,-2,0,0,1,1,0,0},
		  {-6,6,-6,6,-3,-3,3,3,-4,4,2,-2,-2,-2,-1,-1},
		  {4,-4,4,-4,2,2,-2,-2,2,-2,-2,2,1,1,1,1}};
  double xxd,d1d2,cl[16],x[16],d1,d2,y[5],y1[5],y2[5],y12[5];
  double mc2,mb2,eps=1e-6; // q^2 grid points at mc2+eps, mb2+eps

  warn = warn_in;   // option to turn on warning if extrapolating.
  fatal = fatal_in; // option to return zero instead of terminating when invalid input values of x and q are used.

  xmin=1e-6;  // minimum x grid point
  xmax=1.0;   // maximum x grid point
  qsqmin=1.0; // minimum q^2 grid point
  qsqmax=1e9; // maximum q^2 grid point

  // Initialising the x array common to all members of the class.
  // Unfortunately, ANSI-C++ does not allow a initialisation of a 
  // member array.  So here we go...

  xx[0]=0;
  xx[1]=1E-6;
  xx[2]=2E-6;
  xx[3]=4E-6;
  xx[4]=6E-6;
  xx[5]=8E-6;
  xx[6]=1E-5;
  xx[7]=2E-5;
  xx[8]=4E-5;
  xx[9]=6E-5;
  xx[10]=8E-5;
  xx[11]=1E-4;
  xx[12]=2E-4;
  xx[13]=4E-4;
  xx[14]=6E-4;
  xx[15]=8E-4;
  xx[16]=1E-3;
  xx[17]=2E-3;
  xx[18]=4E-3;
  xx[19]=6E-3;
  xx[20]=8E-3;
  xx[21]=1E-2;
  xx[22]=1.4E-2;
  xx[23]=2E-2;
  xx[24]=3E-2;
  xx[25]=4E-2;
  xx[26]=6E-2;
  xx[27]=8E-2;
  xx[28]=.1E0;
  xx[29]=.125E0;
  xx[30]=.15E0;
  xx[31]=.175E0;
  xx[32]=.2E0;
  xx[33]=.225E0;
  xx[34]=.25E0;
  xx[35]=.275E0;
  xx[36]=.3E0;
  xx[37]=.325E0;
  xx[38]=.35E0;
  xx[39]=.375E0;
  xx[40]=.4E0;
  xx[41]=.425E0;
  xx[42]=.45E0;
  xx[43]=.475E0;
  xx[44]=.5E0;
  xx[45]=.525E0;
  xx[46]=.55E0;
  xx[47]=.575E0;
  xx[48]=.6E0;
  xx[49]=.625E0;
  xx[50]=.65E0;
  xx[51]=.675E0;
  xx[52]=.7E0;
  xx[53]=.725E0;
  xx[54]=.75E0;
  xx[55]=.775E0;
  xx[56]=.8E0;
  xx[57]=.825E0;
  xx[58]=.85E0;
  xx[59]=.875E0;
  xx[60]=.9E0;
  xx[61]=.925E0;
  xx[62]=.95E0;
  xx[63]=.975E0;
  xx[64]=1E0;
  
  // ditto for qq array
  
  qq[0]=0;
  qq[1]=1.E0;
  qq[2]=1.25E0;
  qq[3]=1.5E0;
  qq[4]=0;
  qq[5]=0;
  qq[6]=2.5E0;
  qq[7]=3.2E0;
  qq[8]=4E0;
  qq[9]=5E0;
  qq[10]=6.4E0;
  qq[11]=8E0;
  qq[12]=1E1;
  qq[13]=1.2E1;
  qq[14]=0;
  qq[15]=0;
  qq[16]=2.6E1;
  qq[17]=4E1;
  qq[18]=6.4E1;
  qq[19]=1E2;
  qq[20]=1.6E2;
  qq[21]=2.4E2;
  qq[22]=4E2;
  qq[23]=6.4E2;
  qq[24]=1E3;
  qq[25]=1.8E3;
  qq[26]=3.2E3;
  qq[27]=5.6E3;
  qq[28]=1E4;
  qq[29]=1.8E4;
  qq[30]=3.2E4;
  qq[31]=5.6E4;
  qq[32]=1E5;
  qq[33]=1.8E5;
  qq[34]=3.2E5;
  qq[35]=5.6E5;
  qq[36]=1E6;
  qq[37]=1.8E6;
  qq[38]=3.2E6;
  qq[39]=5.6E6;
  qq[40]=1E7;
  qq[41]=1.8E7;
  qq[42]=3.2E7;
  qq[43]=5.6E7;
  qq[44]=1E8;
  qq[45]=1.8E8;
  qq[46]=3.2E8;
  qq[47]=5.6E8;
  qq[48]=1E9;
  
  // The name of the file to open is stored in 'filename'.
  // Line below can be commented out if you don't want this message.
  cout << "Reading PDF grid from " << filename << endl;
  ifstream data_file;
  data_file.open(filename.c_str());

  if (data_file.fail()) {
    cerr << "Error in c_mstwpdf::c_mstwpdf opening " << filename << endl;
    exit (-1);
  }

  // Read distance, tolerance, heavy quark masses
  // and alphaS values from file.
  char comma;
  int nExtraFlavours;
  data_file.ignore(256,'\n');
  data_file.ignore(256,'\n');
  data_file.ignore(256,'='); data_file >> distance >> tolerance;
  data_file.ignore(256,'='); data_file >> mCharm;
  data_file.ignore(256,'='); data_file >> mBottom;
  data_file.ignore(256,'='); data_file >> alphaSQ0;
  data_file.ignore(256,'='); data_file >> alphaSMZ;
  data_file.ignore(256,'='); data_file >> alphaSorder >> comma >> alphaSnfmax;
  data_file.ignore(256,'='); data_file >> nExtraFlavours;
  data_file.ignore(256,'\n');
  data_file.ignore(256,'\n');
  data_file.ignore(256,'\n');
  mc2=mCharm*mCharm;
  mb2=mBottom*mBottom;

  // Check that the heavy quark masses are sensible.
  // Redistribute grid points if not in usual range.
  if (mc2 <= qq[1] || mc2+eps >= qq[8]) {
    cerr << "Error in c_mstwpdf::c_mstwpdf: invalid mCharm = " << mCharm << endl;
    exit (-1);
  }
  else if (mc2 < qq[2]) {
    nqc0 = 2;
    qq[4] = qq[2];
    qq[5] = qq[3];
  }
  else if (mc2 < qq[3]) {
    nqc0 = 3;
    qq[5] = qq[3];
  }
  else if (mc2 < qq[6]) {
    nqc0 = 4;
  }
  else if (mc2 < qq[7]) {
    nqc0 = 5;
    qq[4] = qq[6];
  }
  else {
    nqc0 = 6;
    qq[4] = qq[6];
    qq[5] = qq[7];
  }
  if (mb2 <= qq[12] || mb2+eps >= qq[17]) {
    cerr << "Error in c_mstwpdf::c_mstwpdf: invalid mBottom = " << mBottom << endl;
    exit (-1);
  }
  else if (mb2 < qq[13]) {
    nqb0 = 13;
    qq[15] = qq[13];
  }
  else if (mb2 < qq[16]) {
    nqb0 = 14;
  }
  else {
    nqb0 = 15;
    qq[14] = qq[16];
  }
  qq[nqc0] = mc2;
  qq[nqc0+1] = mc2+eps;
  qq[nqb0] = mb2;
  qq[nqb0+1] = mb2+eps;

  // The nExtraFlavours variable is provided to aid compatibility
  // with future grids where, for example, a photon distribution
  // might be provided (cf. the MRST2004QED PDFs).
  if (nExtraFlavours < 0 || nExtraFlavours > 1) {
    cerr << "Error in c_mstwpdf::c_mstwpdf: invalid nExtraFlavours = " << nExtraFlavours << endl;
    exit (-1);
  }

  // Now read in the grids from the grid file.
  for (n=1;n<=nx-1;n++) 
    for (m=1;m<=nq;m++) {
      for (i=1;i<=9;i++)
	data_file >> f[i][n][m];
      if (alphaSorder==2) { // only at NNLO
	data_file >> f[10][n][m]; // = chm-cbar
	data_file >> f[11][n][m]; // = bot-bbar
      }
      else {
	f[10][n][m] = 0.; // = chm-cbar
	f[11][n][m] = 0.; // = bot-bbar
      }
      if (nExtraFlavours>0)
	data_file >> f[12][n][m];   // = photon
      else
	f[12][n][m] = 0.; // photon
      if (data_file.eof()) {
	cerr << "Error in c_mstwpdf::c_mstwpdf reading " << filename << endl;
	exit (-1);
      }
    }
  
  // Check that ALL the file contents have been read in.
  data_file >> dtemp;
  if (!data_file.eof()) {
    cerr << "Error in c_mstwpdf::c_mstwpdf reading " << filename << endl;
    exit (-1);
  }
  
  // Close the datafile.
  data_file.close();
  
  // PDFs are identically zero at x = 1.
  for (i=1;i<=np;i++)
    for (m=1;m<=nq;m++)
      f[i][nx][m]=0.0;
  
  // Set up the new array in log10(x) and log10(qsq).
  for (i=1;i<=nx;i++)
    xx[i]=log10(xx[i]);
  for (m=1;m<=nq;m++)
    qq[m]=log10(qq[m]);
  
  // Now calculate the derivatives used for bicubic interpolation.
  for (i=1;i<=np;i++) {

    // Start by calculating the first x derivatives
    // along the first x value:
    for (m=1;m<=nq;m++) {
      f1[i][1][m]=polderivative1(xx[1],xx[2],xx[3],f[i][1][m],f[i][2][m],f[i][3][m]);
      // Then along the rest (up to the last):
      for (k=2;k<nx;k++)
	f1[i][k][m]=polderivative2(xx[k-1],xx[k],xx[k+1],f[i][k-1][m],f[i][k][m],f[i][k+1][m]);
      // Then for the last column:
      f1[i][nx][m]=polderivative3(xx[nx-2],xx[nx-1],xx[nx],f[i][nx-2][m],f[i][nx-1][m],f[i][nx][m]);
    }

    // Then calculate the qq derivatives.  At NNLO there are
    // discontinuities in the PDFs at mc2 and mb2, so calculate
    // the derivatives at q^2 = mc2, mc2+eps, mb2, mb2+eps in
    // the same way as at the endpoints qsqmin and qsqmax.
    for (m=1;m<=nq;m++) {
      if (nqc0==2 && m==1) {
	for (k=1;k<=nx;k++)
	  f2[i][k][m]=(f[i][k][m+1]-f[i][k][m])/(qq[m+1]-qq[m]);
      }
      else if (nqc0==2 && m==2) {
	for (k=1;k<=nx;k++)
	  f2[i][k][m]=(f[i][k][m]-f[i][k][m-1])/(qq[m]-qq[m-1]);
      }
      else if (m==1 || m==nqc0+1 || m==nqb0+1) {
	for (k=1;k<=nx;k++)
	  f2[i][k][m]=polderivative1(qq[m],qq[m+1],qq[m+2],
				     f[i][k][m],f[i][k][m+1],f[i][k][m+2]);
      }
      else if (m==nq || m==nqc0 || m==nqb0) {
	for (k=1;k<=nx;k++)
	  f2[i][k][m]=polderivative3(qq[m-2],qq[m-1],qq[m],
				     f[i][k][m-2],f[i][k][m-1],f[i][k][m]);
      }
      else {
	// The rest:
	for (k=1;k<=nx;k++)
	  f2[i][k][m]=polderivative2(qq[m-1],qq[m],qq[m+1],
				    f[i][k][m-1],f[i][k][m],f[i][k][m+1]);
      }
    }
    
    // Now, calculate the cross derivatives.
    // Calculate these as the average between (d/dx)(d/dy) and (d/dy)(d/dx).
    
    // First calculate (d/dx)(d/dy).
    // Start by calculating the first x derivatives
    // along the first x value:
    for (m=1;m<=nq;m++)
      f12[i][1][m]=polderivative1(xx[1],xx[2],xx[3],f2[i][1][m],f2[i][2][m],f2[i][3][m]);
    // Then along the rest (up to the last):
    for (k=2;k<nx;k++) {
      for (m=1;m<=nq;m++)
	f12[i][k][m]=polderivative2(xx[k-1],xx[k],xx[k+1],f2[i][k-1][m],f2[i][k][m],f2[i][k+1][m]);
    }
    // Then for the last column:
    for (m=1;m<=nq;m++)
      f12[i][nx][m]=polderivative3(xx[nx-2],xx[nx-1],xx[nx],f2[i][nx-2][m],f2[i][nx-1][m],f2[i][nx][m]);
    
    // Now calculate (d/dy)(d/dx).
    for (m=1;m<=nq;m++) {
      if (nqc0==2 && m==1) {
	for (k=1;k<=nx;k++)
	  f21[i][k][m]=(f1[i][k][m+1]-f1[i][k][m])/(qq[m+1]-qq[m]);
      }
      else if (nqc0==2 && m==2) {
	for (k=1;k<=nx;k++)
	  f21[i][k][m]=(f1[i][k][m]-f1[i][k][m-1])/(qq[m]-qq[m-1]);
      }
      else if (m==1 || m==nqc0+1 || m==nqb0+1) {
	for (k=1;k<=nx;k++)
	  f21[i][k][m]=polderivative1(qq[m],qq[m+1],qq[m+2],
				      f1[i][k][m],f1[i][k][m+1],f1[i][k][m+2]);
      }
      else if (m==nq || m==nqc0 || m==nqb0) {
	for (k=1;k<=nx;k++)
	  f21[i][k][m]=polderivative3(qq[m-2],qq[m-1],qq[m],
				      f1[i][k][m-2],f1[i][k][m-1],f1[i][k][m]);
      }
      else {
	// The rest:
	for (k=1;k<=nx;k++)
	  f21[i][k][m]=polderivative2(qq[m-1],qq[m],qq[m+1],
				     f1[i][k][m-1],f1[i][k][m],f1[i][k][m+1]);
      }
    }

    // Now take the average of (d/dx)(d/dy) and (d/dy)(d/dx).
    for (k=1;k<=nx;k++) {
      for (m=1;m<=nq;m++) {
	f12[i][k][m] = 0.5*(f12[i][k][m]+f21[i][k][m]);
      }
    }

    // Now calculate the coefficients c_ij.
    for (n=1;n<=nx-1;n++) {
      for (m=1;m<=nq-1;m++) {
	d1=xx[n+1]-xx[n];
	d2=qq[m+1]-qq[m];
	d1d2=d1*d2;
	
	y[1]=f[i][n][m];
	y[2]=f[i][n+1][m];
	y[3]=f[i][n+1][m+1];
	y[4]=f[i][n][m+1];
	
	y1[1]=f1[i][n][m];
	y1[2]=f1[i][n+1][m];
	y1[3]=f1[i][n+1][m+1];
	y1[4]=f1[i][n][m+1];
	
	y2[1]=f2[i][n][m];
	y2[2]=f2[i][n+1][m];
	y2[3]=f2[i][n+1][m+1];
	y2[4]=f2[i][n][m+1];
	
	y12[1]=f12[i][n][m];
	y12[2]=f12[i][n+1][m];
	y12[3]=f12[i][n+1][m+1];
	y12[4]=f12[i][n][m+1];
	
	for (k=1;k<=4;k++) {
	  x[k-1]=y[k];
	  x[k+3]=y1[k]*d1;
	  x[k+7]=y2[k]*d2;
	  x[k+11]=y12[k]*d1d2;
	}
	
	for (l=0;l<=15;l++) {
	  xxd=0.0;
	  for (k=0;k<=15;k++) xxd+= wt[l][k]*x[k];
	  cl[l]=xxd;
	}
	
	l=0;
	for (k=1;k<=4;k++) 
	  for (j=1;j<=4;j++) c[i][n][m][k][j]=cl[l++];
      } //m
    } //n
  } // i

}

void c_mstwpdf::update(double x,double q)
  // Updates the parton content.
{
  double dn,up,sv,cv,bv;

  // Quarks:
  dn = parton(1,x,q);
  up = parton(2,x,q);
  cont.str = parton(3,x,q);
  cont.chm = parton(4,x,q);
  cont.bot = parton(5,x,q);

  // Valence quarks:
  cont.dnv = parton(7,x,q);
  cont.upv = parton(8,x,q);
  sv = parton(9,x,q);
  cv = parton(10,x,q);
  bv = parton(11,x,q);
  
  // Antiquarks = quarks - valence quarks:
  cont.dsea = dn - cont.dnv;
  cont.usea = up - cont.upv;
  cont.sbar = cont.str - sv;
  cont.cbar = cont.chm - cv;
  cont.bbar = cont.bot - bv;

  // Gluon:
  cont.glu = parton(0,x,q);

  // Photon (= zero unless considering QED contributions):
  cont.phot = parton(13,x,q);
}

double c_mstwpdf::parton(int f,double x,double q)
  // Returns the PDF value for parton of flavour 'f' at x,q.
{
  double qsq;
  int ip;
  int interpolate(1);
  double parton_pdf=0,parton_pdf1=0,anom;
  double xxx,qqq;

  qsq=q*q;

  // If mc2 < qsq < mc2+eps, then qsq = mc2+eps.
  if (qsq>pow(10.,qq[nqc0]) && qsq<pow(10.,qq[nqc0+1])) {
    qsq = pow(10.,qq[nqc0+1]);
  }
  
  // If mb2 < qsq < mb2+eps, then qsq = mb2+eps.
  if (qsq>pow(10.,qq[nqb0]) && qsq<pow(10.,qq[nqb0+1])) {
    qsq = pow(10.,qq[nqb0+1]);
  }

  if (x<xmin) {
    interpolate=0;
    if (x<=0.) {
      if (warn||fatal) cerr << "Error in c_mstwpdf::parton, x = " << x << endl;
      if (fatal) exit (-1);
      else return 0.;
    }
  }
  else if (x>xmax) {
    interpolate=0;
    if (warn||fatal) cerr << "Error in c_mstwpdf::parton, x = " << x << endl;
    if (fatal) exit (-1);
    else return 0.;
  }

  if (qsq<qsqmin) {
    interpolate=-1;
    if (q<=0.) {
      if (warn||fatal) cerr << "Error in c_mstwpdf::parton, q = " << q << endl;
      if (fatal) exit (-1);
      else return 0.;
    }
  }
  else if (qsq>qsqmax) {
    interpolate=0;
  }
  
  if (f==0) ip=1;
  else if (f>=1 && f<=5) ip=f+1;
  else if (f<=-1 && f>=-5) ip=-f+1;
  else if (f>=7 && f<=11) ip=f;
  else if (f==13) ip=12;
  else if (abs(f)==6 || f==12) return 0.;
  else {
    if (warn||fatal) cerr << "Error in c_mstwpdf::parton, f = " << f << endl;
    if (fatal) exit(-1);
    else return 0.;
  }

  // Interpolation in log10(x), log10(qsq):
  xxx=log10(x);
  qqq=log10(qsq);

  if (interpolate==1) { // do usual interpolation
    parton_pdf=parton_interpolate(ip,xxx,qqq);
    if (f<=-1 && f>=-5) // antiquark = quark - valence
      parton_pdf -= parton_interpolate(ip+5,xxx,qqq);
  }
  else if (interpolate==-1) { // extrapolate to low Q^2
    
    if (x<xmin) { // extrapolate to low x
      parton_pdf = parton_extrapolate(ip,xxx,log10(qsqmin));
      parton_pdf1 = parton_extrapolate(ip,xxx,log10(1.01*qsqmin));
      if (f<=-1 && f>=-5) { // antiquark = quark - valence
	parton_pdf -= parton_extrapolate(ip+5,xxx,log10(qsqmin));
	parton_pdf1 -= parton_extrapolate(ip+5,xxx,log10(1.01*qsqmin));
      }
    }
    else { // do usual interpolation
      parton_pdf = parton_interpolate(ip,xxx,log10(qsqmin));
      parton_pdf1 = parton_interpolate(ip,xxx,log10(1.01*qsqmin));
      if (f<=-1 && f>=-5) { // antiquark = quark - valence
	parton_pdf -= parton_interpolate(ip+5,xxx,log10(qsqmin));
	parton_pdf1 -= parton_interpolate(ip+5,xxx,log10(1.01*qsqmin));
      }
    }
    // Calculate the anomalous dimension, dlog(xf)/dlog(qsq),
    // evaluated at qsqmin.  Then extrapolate the PDFs to low
    // qsq < qsqmin by interpolating the anomalous dimenion between
    // the value at qsqmin and a value of 1 for qsq << qsqmin.
    // If value of PDF at qsqmin is very small, just set
    // anomalous dimension to 1 to prevent rounding errors.
    // Impose minimum anomalous dimension of -2.5.
    if (fabs(parton_pdf) >= 1.e-5)
      anom = max( -2.5, (parton_pdf1-parton_pdf)/parton_pdf/0.01 );
    else anom = 1.;
    parton_pdf = parton_pdf*pow(qsq/qsqmin,anom*qsq/qsqmin+1.-qsq/qsqmin);

  }
  else { // extrapolate outside PDF grid to low x or high Q^2
    if (warn)
      cerr << "Warning in c_mstwpdf::parton, extrapolating: f = " 
	   << f << ", x = " << x << ", q = " << q << endl;
    parton_pdf = parton_extrapolate(ip,xxx,qqq);
    if (f<=-1 && f>=-5) // antiquark = quark - valence
      parton_pdf -= parton_extrapolate(ip+5,xxx,qqq);
  }

  return parton_pdf;
}

double c_mstwpdf::parton_interpolate(int ip, double xxx, double qqq)
{
  double g;
  int n,m,l;
  double t,u;

  n=locate(xx,nx,xxx); // 0: below xmin, nx: above xmax
  m=locate(qq,nq,qqq); // 0: below qsqmin, nq: above qsqmax
  
  t=(xxx-xx[n])/(xx[n+1]-xx[n]);
  u=(qqq-qq[m])/(qq[m+1]-qq[m]);
  
  g=0.0;
  for (l=4;l>=1;l--) {
    g=t*g+((c[ip][n][m][l][4]*u+c[ip][n][m][l][3])*u
	   +c[ip][n][m][l][2])*u+c[ip][n][m][l][1];
  }
  
  return g;
}

double c_mstwpdf::parton_extrapolate(int ip, double xxx, double qqq)
{
  double parton_pdf=0.;
  int n,m;

  n=locate(xx,nx,xxx); // 0: below xmin, nx: above xmax
  m=locate(qq,nq,qqq); // 0: below qsqmin, nq: above qsqmax
  
  if (n==0&&(m>0&&m<nq)) { // if extrapolation in small x only
    
    double f0,f1;
    f0=parton_interpolate(ip,xx[1],qqq);
    f1=parton_interpolate(ip,xx[2],qqq);
    if ( f0>1e-3 && f1>1e-3 ) { // if values are positive, keep them so
      f0=log(f0);
      f1=log(f1);
      parton_pdf=exp(f0+(f1-f0)/(xx[2]-xx[1])*(xxx-xx[1]));
    } else // otherwise just extrapolate in the value
      parton_pdf=f0+(f1-f0)/(xx[2]-xx[1])*(xxx-xx[1]); 
    
  } if (n>0&&m==nq) { // if extrapolation into large q only
    
    double f0,f1;
    f0=parton_interpolate(ip,xxx,qq[nq]);
    f1=parton_interpolate(ip,xxx,qq[nq-1]);
    if ( f0>1e-3 && f1>1e-3 ) { // if values are positive, keep them so
      f0=log(f0);
      f1=log(f1);
      parton_pdf=exp(f0+(f0-f1)/(qq[nq]-qq[nq-1])*(qqq-qq[nq]));
    } else // otherwise just extrapolate in the value
      parton_pdf=f0+(f0-f1)/(qq[nq]-qq[nq-1])*(qqq-qq[nq]);
    
  } if (n==0&&m==nq) { // if extrapolation into large q AND small x
    
    double f0,f1;
    f0=c_mstwpdf::parton_extrapolate(ip,xx[1],qqq);
    f1=c_mstwpdf::parton_extrapolate(ip,xx[2],qqq);
    if ( f0>1e-3 && f1>1e-3 ) { // if values are positive, keep them so
      f0=log(f0);
      f1=log(f1);
      parton_pdf=exp(f0+(f1-f0)/(xx[2]-xx[1])*(xxx-xx[1]));
    } else // otherwise just extrapolate in the value
      parton_pdf=f0+(f1-f0)/(xx[2]-xx[1])*(xxx-xx[1]);       
    
  }
  
  return parton_pdf;
}
