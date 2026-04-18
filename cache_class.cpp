#include<iostream>
#include<fstream>
#include "cache_class.h"
#include <cmath>

using namespace std;

Cache::Cache(int num_entries, int assoc, int block_size){
  this->num_entries = num_entries;
  this->assoc = assoc;
  this->num_sets = num_entries / assoc;
  this->lru_counter = 0;
  this->block_size = block_size;

  //row is a set, column is a way;
  entries = new Entry*[num_sets];
  for(int i = 0; i < num_sets; i++){
    entries[i] = new Entry[assoc];
  }
}

int Cache::get_index(unsigned long addr){
  return (addr / block_size) % num_sets;
}


int Cache::get_tag(unsigned long addr){
  return addr / (block_size * num_sets);
}

int Cache::get_offset(unsigned long addr){
  return addr % block_size;
}

// 2 conditions for a hit: 1) Valid bit is true 2) tag matches entry tag
bool Cache::hit(ofstream& outfile, unsigned long addr){
  int index = get_index(addr);
  int tag = get_tag(addr);

  for(int i = 0; i < assoc; i++){
    if(entries[index][i].get_valid() && entries[index][i].get_tag() == tag){
      return true;
    }
  }
  return false;
}

void Cache::update(ofstream& outfile, unsigned long addr){
  int index = get_index(addr);
  int tag = get_tag(addr);

  //check for invalid slot
  for(int slot = 0; slot < assoc; slot++){
    if(!entries[index][slot].get_valid()){
      entries[index][slot].set_valid(true);
      entries[index][slot].set_tag(tag);
      entries[index][slot].set_ref(lru_counter);
      lru_counter++;
      return;
    }
  }

  //if no invalid slot, remove LRU entry
  int lru_victim = 0;
  int lru_ref = entries[index][0].get_ref();

  for(int slot = 1; slot < assoc; slot++){
    if(entries[index][slot].get_ref() < lru_ref){
      lru_victim = slot;
      lru_ref = entries[index][slot].get_ref();
    }
  }

  entries[index][lru_victim].set_ref(lru_counter);
  entries[index][lru_victim].set_tag(tag);

  lru_counter++;
}

Cache::~Cache(){
  for(int i = 0; i < num_sets; i++){
    delete[] entries[i];
  }
  delete[] entries;
}

Entry::Entry(){
  valid = false;
  tag = 0;
  ref = 0;
}

Entry::~Entry(){
}

void Entry::display(ofstream& outfile){

  
}