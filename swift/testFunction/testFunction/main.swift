//
//  main.swift
//  testFunction
//
//  Created by sijiewang on 4/15/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

import Foundation

println("Hello, World!")

func sayHello(personName: String) -> String {
    let greeting = "Hello, " + personName + "!"
    return greeting
}

println(sayHello("Anna"))
println(sayHello("Brian"))

func halfOpenRangeLength(start: Int, end: Int) -> Int {
    return end - start
}

println(halfOpenRangeLength(1, 10))

func count1(string: String) -> (vowels: Int, consonants: Int, others: Int) {
    var vowels = 0, consontants = 0, others = 0
    for character in string {
        switch String(character).lowercaseString {
            case "a", "e", "i", "o", "u":
                ++vowels
            case "b", "c", "d", "f", "g", "h", "j":
                ++consontants
        default:
            ++others
        }
    }
    return (vowels, consontants, others)
}

let total = count1("some arbitary string!")
println("\(total.vowels) vowels and \(total.consonants) consonants")

func join2(s1: String, s2: String, joiner: String) -> String {
    return s1 + joiner + s2
}

func join(string s1: String, toString s2: String, withJoiner joiner: String) -> String {
    return s1 + joiner + s2
}

println(join(string: "hello", toString: "word", withJoiner: ", "))

func containsCharacter(#string: String, #characterToFind: Character) -> Bool {
    for character in string {
        if character == characterToFind {
            return true
        }
    }
    return false
}

let containerAVee = containsCharacter(string: "aardvark", characterToFind: "v")
println(containerAVee)

func arithmeticMean(numbers: Double...) -> Double {
    var total: Double = 0
    for number in numbers {
        total += number
    }
    return total / Double(numbers.count)
}
println(arithmeticMean(1, 2, 3, 4, 5))

func alignRight(var string: String, count1: Int, pad: Character) -> String {
    let amountToPad = count1 - count(string)
    for _ in 1...amountToPad {
        string = String(pad) + string
    }
    return string
}

func swapTwoInts(inout a: Int, inout b: Int) {
    let temporary = a
    a = b
    b = temporary
}
var someInt = 3
var anotherInt = 107
swapTwoInts(&someInt, &anotherInt)
println("someInt is now \(someInt), anotherInt is now \(anotherInt)")

func addTwoInts(one: Int, another: Int) -> Int {
    return one + another
}
var mathFunction: (Int, Int) -> Int = addTwoInts
println("Result: \(mathFunction(2, 3))")

func printMathResult(mathFunction: (Int, Int) -> Int, a: Int, b:Int) {
    println("Result: \(mathFunction(a, b))")
}
printMathResult(addTwoInts, 3, 5)

func stepForward(input: Int) -> Int {
    return input + 1
}
func stepBackward(input: Int) -> Int {
    return input - 1
}

func chooseStepFunction(backwards: Bool) -> (Int) -> Int {
    return backwards ? stepBackward : stepForward
}

var currentValue = 3
let moveNearerToZero2 = chooseStepFunction(currentValue > 0)

func chooseStepFunction2(backwards: Bool) -> (Int) -> Int {
    func stepForward(input: Int) -> Int {
        return input + 1
    }
    func stepBackward(input: Int) -> Int {
        return input - 1
    }
    return backwards ? stepBackward : stepForward
}

var currentValue2 = -4
let moveNearerToZero = chooseStepFunction2(currentValue2 > 0)
while currentValue2 != 0 {
    println("\(currentValue2) ...")
    currentValue2 = moveNearerToZero(currentValue2)
}
println("zero!")

var names = ["Charis", "Alex", "Ewa","Barry", "Daniella"]
func backwards3(s1: String, s2: String) -> Bool {
    return s1 > s2
}
//var reversed = sort(&names, backwards3)
println(names)

var reversed2 = sort(&names, { (s1: String, s2: String) -> Bool in return s1 > s2 } )
println(names)

func someFunctionThatTakesAClosure(closure: () -> ()) {
    
}

let digitNames = [
    0: "Zero", 1: "One", 2: "two", 3: "Three", 4: "Foure",
    5: "Five", 6: "Six", 7: "Seven", 8: "Eight", 9: "Nine"
]

let numbers = [16, 58, 510]
let strings = numbers.map{
    (var number)->String in
    var output = ""
    while number > 0 {
        output = digitNames[number % 10]! + output
        number /= 10
    }
    return output
}
println(strings)

func makeIncrementor(forIncrement amount: Int) -> () -> Int {
    var runningTotal = 0
    func incrementor() -> Int {
        runningTotal += amount
        return runningTotal
    }
    return incrementor
}
let incrementByTen = makeIncrementor(forIncrement: 10)
println(incrementByTen())
println(incrementByTen())

enum CompassPoint {
    case North
    case South
    case East
    case West
}
var directionToHead = CompassPoint.West

enum Barcode {
    case UPCA(Int, Int, Int)
    case QRCode(String)
}
var productBarcode = Barcode.UPCA(8, 85909_51226, 3)
productBarcode = .QRCode("ABCDEFGHIJKLMNOP")
switch productBarcode {
case .UPCA(let numberSystem, let identifier, let check):
    println("UPC-A with value of \(numberSystem), \(identifier), \(check).")
case .QRCode(let productCode):
    println("QR code with value of \(productCode)")
}

enum ASCIIControlCharacter: Character {
    case Tab = "\t"
    case LineFeed = "\n"
    case CarriageReturn = "\r"
}
enum Planet: Int {
    case Mercury = 1, Venus, Earth, Mars, Jupiter, Satrun, Uranus, Neptune
}
let earthsOrder = Planet.Earth.rawValue
println(earthsOrder)


