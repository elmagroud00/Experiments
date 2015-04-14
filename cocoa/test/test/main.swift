//
//  main.swift
//  test
//
//  Created by sijiewang on 4/14/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

import Foundation

var shoppingList = ["mac", "iphone", "ipad"];

for item in shoppingList {
    println(item);
}

for(index, value) in enumerate(shoppingList) {
    println("Item \(index + 1) : \(value)");
}

var threeDoubles = [Double](count: 3, repeatedValue: 0.0);

for item in threeDoubles {
    println(item);
}

var anotherThreeDoubles = Array(count:3, repeatedValue:2.5);
for item in anotherThreeDoubles {
    println(item);
}

var airports:Dictionary<String, String> = ["TYO" : "Tokyo", "DUB" : "Dublin"];
println("The dictionary of airports contains \(airports.count) items");

airports["LHR"] = "London";

if let oldValue = airports.updateValue("Dublin Internation", forKey: "DUB") {
    println("The old value for DUB was \(oldValue)");
}

airports["APL"] = "Apple Internaion";
airports["APL"] = nil;

if let removeValue = airports.removeValueForKey("DUB") {
    println("The removed airport's name is \(removeValue).");
} else {
    println("The airports dictionary does not contain a value for DUB.");
}

for(airportCode, airportName) in airports {
    println("\(airportCode): \(airportName)");
}

for airportCode in airports.keys {
    println("Airport code: \(airportCode)");
}
for airportName in airports.values {
    println("Airport name: \(airportName)");
}

let airportCodes = Array(airports.keys);
for name in airportCodes {
    println(name);
}

var namesOfIntegers = Dictionary<Int, String>();
namesOfIntegers[16] = "sixteen";
for (num, value) in namesOfIntegers {
    println("num = \(num), value = \(value)");
}
namesOfIntegers = [:];
println(namesOfIntegers.count);

for index in 1 ... 5 {
    println("\(index) times 5 is \(index * 5)");
}

let base = 3;
let power = 10;
var answer = 1;

for _ in 1 ... power {
    answer *= base;
}

println("\(base) to the power of \(power) is \(answer)");

for character in "Hello" {
    println(character);
}

for var index = 0; index < 3; ++index {
    println("index is \(index)");
}

var index : Int;
for index = 0; index < 3; ++index {
    println("index is \(index)");
}

let finalSquare = 25;
var board = [Int](count:finalSquare + 1, repeatedValue:0);
board[03] = +08; board[06] = +11; board[09] = +09; board[10] = +01;
board[14] = -10; board[19] = -11; board[22] = -02; board[24] = -08;

var square = 0
var diceRoll = 0
while square < finalSquare {
    if ++diceRoll == 7 { diceRoll = 1 }
    square += diceRoll
    
    if square < board.count {
        square += board[square]
    }
}
println("Game Over")

let someCharacter : Character = "e"
switch someCharacter {
case "a", "e", "i", "o", "u":
    println("\(someCharacter) is a vowel")
case "b", "c", "d" :
    println("\(someCharacter) is a consonant");
default:
    println("\(someCharacter) is not a vowel or a consont");
}

let count = 3_000_000_000_000
let countedThings = "starts in the Milky      Way"
var naturalCount : String

switch count {
case 0:
    naturalCount = "no"
case 1 ... 3:
    naturalCount = "a few"
case 4 ... 9:
    naturalCount = "serveral"
default:
    naturalCount = "millions and millions of"
}

println("There are \(naturalCount) \(countedThings).");