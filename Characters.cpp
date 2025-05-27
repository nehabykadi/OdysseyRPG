#include <iostream>
#include <string>
#include "Characters.h"

using namespace std;

Character::Character() {
    _name = "";
    _age = 1;
    _strength = 100;
    _stamina = 100;
    _wisdom = 100;
    _pride_points = 0;
    _advisor = "N/A";

}

Character::Character(string name, int age, int strength, int stamina, int wisdom, int pride_points) {
    _name = name;
     if (strength >= 100 && strength <= 1000) {
        _strength = strength;
    } else {
        _strength = 100; 
    }
    if (stamina >= 100 && stamina <= 1000) {
        _stamina = stamina;
    } else {
        _stamina = 100;  
    }
    if (wisdom >= 100 && wisdom <= 1000) {
        _wisdom = wisdom;
    } else {
        _wisdom = 100;  
    }

    _pride_points = 0;
    _age = 1;
}

string Character::getName()
{
    return _name;
}

int Character::getStrength()
{
    return _strength;
}

int Character::getStamina()
{
    return _stamina;
}

int Character::getWisdom()
{
    return _wisdom;
}

int Character::getPridePoints()
{
    return _pride_points;
}

int Character::getAge()
{
    return _age;
}

string Character::getAdvisor()
{
    return _advisor;
}

void Character::setName(string name){
    _name = name;
}

void Character::setStrength(int strength) {
    if (strength >= 100 && strength <= 1000) {
        _strength = strength;
    }
}

void Character::setStamina(int stamina) {
    if (stamina >= 100 && stamina <= 1000) {
        _stamina = stamina;
    }
}

void Character::setWisdom(int wisdom) {
    if (wisdom >= 100 && wisdom <= 1000) {
        _wisdom = wisdom;
    }
}

void Character::setPridePoints(int pride_points){
    _pride_points = pride_points;
}

void Character::setAge(int age){
    if (age >= 1 && age <= 20) {
        _age = age;
    }
}

void Character:: setAdvisor(string advisor){
    _advisor = advisor;
}

void Character::trainCub(int strength, int stamina, int wisdom) {
    _strength += strength;
    _stamina += stamina;
    _wisdom += wisdom;
    _pride_points -= 5000;
}

void Character::toPrideLands(int strength, int stamina, int wisdom) {
    _strength += strength;
    _stamina += stamina;
    _wisdom += wisdom;
    _pride_points += 1500;
}

void Character::printStats(){
    cout << "Player: " << _name << endl;
    cout << "Age: " << _age << " years" << endl;
    cout << "Strength: " << _strength << endl;
    cout << "Stamina: " << _stamina << endl;
    cout << "Wisdom: " << _wisdom << endl;
    cout << "Pride Points: " << _pride_points << endl;
    cout << "Advisor: " << _advisor << endl;
}
