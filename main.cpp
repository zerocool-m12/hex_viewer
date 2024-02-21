#include<iostream>
#include<vector>
#include<filesystem>
#include<fstream>
#include<string>
#include<iomanip>
std::string path_prompt();
void process(const std::string&);
int main(int argc,char*argv[]){
  std::string path;
  if(argc >1){
    path = argv[1];
    if(not std::filesystem::exists(path) or not std::filesystem::is_regular_file(path)){
      std::cerr<<"FAWAZ_HEX: "<<argv[1]<<" No such file or directory"<<std::endl;
      exit(EXIT_FAILURE);
     }else
      process(path);
    }else{
      path = path_prompt();
      process(path);
     }
  return EXIT_SUCCESS;
}
std::string path_prompt(){
  std::cout<<"Please enter the path of the file:-"<<std::endl;
  std::string path;
  while(true){
    std::getline(std::cin,path);
    if(std::filesystem::exists(path) and std::filesystem::is_regular_file(path))
      break;
    else{
      std::cerr<<"FAWAZ_HEX: "<<path<<" No such file or directory"<<std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return path;
}
void process(const std::string&path){
 std::fstream file(path,std::ios::binary|std::ios::in|std::ios::out);
  if(not file.is_open()){
    std::cerr<<"Unable to open the file!"<<std::endl;
    exit(EXIT_FAILURE);
    }
  std::vector<char>buff((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
  size_t counter = 0,address = 0;
  bool space = false;
  std::string temp = "";
  if(buff.data() == nullptr){
    std::cerr<<"Unable to read the file!"<<std::endl;
    exit(EXIT_FAILURE);
  }
  for(int i = 0;i<buff.size();i++){
    if(counter == 0){
      std::cout<<std::uppercase<<std::setw(8)<<std::setfill('0')<<std::hexfloat<<std::hex<<16*address++<<": ";   // this is how to write a hexidecimal number in 16 bit format
      std::cout<<std::uppercase<<std::setw(2)<<std::setfill('0')<<std::hex<<(static_cast<short int>(buff[i]) bitand 0xff);
      if(not isprint(buff[i])) temp.push_back('.');
      else temp.push_back(buff[i]);
      space = not(space);
      counter++;
      }
   else if(counter>0 and counter <15 and space == true){
      std::cout<<std::uppercase<<std::setw(2)<<std::setfill('0')<<std::hex<<(static_cast<short int>(buff[i]) bitand 0xff)<<" ";  // masking
      space = false;
      if(not isprint(buff[i])) temp.push_back('.');
      else temp.push_back(buff[i]);
      counter++;
      }
    else if (counter >0 and counter <15 and space == false){
      std::cout<<std::uppercase<<std::setw(2)<<std::setfill('0')<<std::hex<<(static_cast<short int>(buff[i]) bitand 0xff);
      space = true;
      if(not isprint(buff[i])) temp.push_back('.');
      else temp.push_back(buff[i]);
      counter++;
      }
   else if(counter == 15){
      std::cout<<std::uppercase<<std::setw(2)<<std::setfill('0')<<std::hex<<(static_cast<short int>(buff[i]) bitand 0xff)<<"  ";
      if(not isprint(buff[i])) temp.push_back('.');
      else temp.push_back(buff[i]);
      std::cout<<temp<<std::endl;
      counter = 0;
      temp.clear();
      space = false;
      }
   }
  if(space == false){
    temp.insert(0,32-((counter)*2)+((15-counter)/2)+(2),' ');
    }
  else{
    temp.insert(0,32-((counter)*2)+((15-counter)/2)+(2),' ');
    }
  std::cout<<temp<<std::endl;
  file.close();
}
