#include <iostream>
#include <map>
int main(void) {

  std::map<std::string, int> records;

  records["Alice"] = 5;
  records["Bob"] = 10;

  for ( std::map<std::string,int>::const_iterator i = records.begin(); 
	i != records.end(); ++i ) {
    std::cout << i->first << " : " << i->second << std::endl;
  }

  return 0;
}
