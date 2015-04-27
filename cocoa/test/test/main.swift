//
//  main.swift
//  test
//
//  Created by sijiewang on 4/14/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

let numberSymbol: Character = "三"
var possibleIntegerValue: Int?
switch numberSymbol {
case "1", "一":
    possibleIntegerValue = 1
case "3", "三":
    possibleIntegerValue = 3
default:
    break
}
if let integerValue = possibleIntegerValue {
    println("The integer value of \(numberSymbol) is \(integerValue)")
} else {
    println("An integer value could not be found for \(numberSymbol)")
}


import Foundation

let puzzleInput = "great minds think alike"
var puzzleOutput = ""
for character in puzzleInput {
    switch character {
        case "a", "e", "i", "o", "u", " ":
            continue
    default:
        break
        puzzleOutput += String(character)
    }
}
println(puzzleOutput)

let yetAnotherPoint = (1, -1)
switch yetAnotherPoint {
case let(x, y) where x == y:
    println("(\(x), \(y)) is on the line x == y")
case let(x, y) where x == -y:
    println("(\(x), \(y)) is on the line x == -y")
case let(x, y):
    println("(\(x), \(y)) is just some arbitary point")
}

let anotherPoint = (2, 2)
switch anotherPoint {
case (let x, 0):
    println("on the x-axis with an x value of \(x)")
case (0, let y):
    println("on the y-axis with an y value of \(y)")
case (let x, let y):
    println("somewhere else at (\(x), \(y))")
}

let somepoint = (1, 1)
switch somepoint {
case (0, 0):
    println("(0, 0) is at the orign")
case (_, 0):
    println("(\(somepoint.0), 0) is on the x-axis")
case (0, _):
    println("(0, \(somepoint.1)) is on the y-axis")
case (-2...2, -2...2):
    println("(\(somepoint.0), \(somepoint.1)) is inside the box")
default:
    println("(\(somepoint.0), \(somepoint.1)) is ouside the box")
}

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

