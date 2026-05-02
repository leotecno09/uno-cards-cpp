#pragma once

#include <iostream>
#include <array>

enum class Color {
    Red,
    Green,
    Blue,
    Yellow,
    Black
};

//constexpr std::array<Color, 4> colors = {Color::Red, Color::Green, Color::Blue, Color::Yellow};

enum class Value {
    Zero,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Skip,
    Reverse,
    Draw2,
    Draw4,
    ChangeColor
};

class Card {
private:
    Color color;
    Value value;
    
public:
    Card(Color c, Value v) : color(c), value(v) {}
    
    const Color getColor() const { return color; }
    const Value getValue() const { return value; }
    
    void setColor(Color color) { this->color = color; }
    //void setValue(Value value) { this->value = value; }
    
    bool isPlayable(const Card& topCard) {
        return topCard.color == color || topCard.value == value || color == Color::Black;
    }
    
    void print() {
        switch (value) {
            case Value::Skip: std::cout << "Salta Giro "; break;
            case Value::Reverse: std::cout << "Reverse "; break;
            case Value::Draw2: std::cout << "Pesca 2 "; break;
            case Value::ChangeColor: std::cout << "Cambia Colore "; break;
            case Value::Draw4: std::cout << "Pesca 4 "; break;
            case Value::Zero: std::cout << "Zero "; break;
            case Value::One: std::cout << "Uno "; break;
            case Value::Two: std::cout << "Due "; break;
            case Value::Three: std::cout << "Tre "; break;
            case Value::Four: std::cout << "Quattro "; break;
            case Value::Five: std::cout << "Cinque "; break;
            case Value::Six: std::cout << "Sei "; break;
            case Value::Seven: std::cout << "Sette "; break;
            case Value::Eight: std::cout << "Otto "; break;
            case Value::Nine: std::cout << "Nove "; break;
        }
        
        switch (color) {
            case Color::Black: std::cout << ""; break;
            case Color::Blue: std::cout << "Blu"; break;
            case Color::Green: std::cout << "Verde"; break;
            case Color::Red: std::cout << "Rosso"; break;
            case Color::Yellow: std::cout << "Giallo"; break;
        }
    }
};
