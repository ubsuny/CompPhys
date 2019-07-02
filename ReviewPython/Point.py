class Point:
    x_ = 0.
    y_ = 0.

    def __init__( self, x=0.,y=0.) :
        self.x_ = x
        self.y_ = y

    def __add__( self, right ):
        return Point( self.x_ + right.x_, self.y_ + right.y_ )

    def __sub__( self, right ):
        return Point( self.x_ - right.x_, self.y_ - right.y_ )

    def __str__(self ):
        return '(' + str( self.x_ ) + ',' + str(self.y_) + ')'

    def input(self, line):
        self.x_, self.y_ = [s.strip() for s in line.split(",")]

    
