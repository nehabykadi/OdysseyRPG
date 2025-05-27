#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <string>
#include <iostream>
using namespace std;

class Character {
private:
    string _name;
    int _age;
    int _strength;
    int _stamina;
    int _wisdom;
    int _pride_points;
    string _advisor;
    

public:
    Character(); 
    Character(string name, int age, int strength, int stamina, int wisdom, int pride_points); 
    string getName();
    int getStrength();
    int getStamina();
    int getWisdom();
    int getPridePoints();
    int getAge();
    string getAdvisor();
    void setName(string name);
    void setStrength(int strength);
    void setStamina(int stamina);
    void setWisdom(int wisdom);
    void setPridePoints(int pride_points);
    void setAge(int age);
    void setAdvisor(string advisor);
    void trainCub(int strength, int stamina, int wisdom);
    void toPrideLands(int strength, int stamina, int wisdom);
    void printStats();

};

#endif