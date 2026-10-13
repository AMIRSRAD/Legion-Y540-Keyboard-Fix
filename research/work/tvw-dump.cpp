#include "TeboBoard.hpp"
#include <fstream>
#include <iostream>
int main(int argc,char**argv){
 setvbuf(stdout,nullptr,_IONBF,0); if(argc!=3)return 2;
 Tebo::Board b;std::ifstream in(argv[1],std::ios::binary);b.Read(in);
 std::ofstream out(argv[2]);out<<"ref\tpin\tnet\tdesc\tvalue\tlayer\tpad\n";
 for(auto&p:b.Parts)for(auto&pin:p.Pins){
  auto*l=dynamic_cast<Tebo::LogicLayer*>(b.Layers.at(p.Layer).get());
  if(!l || pin.Handle%8 || pin.Handle/8>=l->Pads.size())return 3;
  auto &pad=l->Pads[pin.Handle/8];
  std::string net=pad.Net>=0?b.Nets.at(pad.Net):"NC";
  out<<p.Name<<'\t'<<pin.Name<<'\t'<<net<<'\t'<<p.Desc<<'\t'<<p.Value<<'\t'<<p.Layer<<'\t'<<pin.Handle/8<<'\n';
 }
}
