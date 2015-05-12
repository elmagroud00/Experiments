//
//  main.swift
//  testFunction
//
//  Created by sijiewang on 4/15/15.
//  Copyright (c) 2015 lnmcc. All rights reserved.
//

import Foundation

class Person113 {
    var residence: Residence113?
}

class Room113 {
    let name: String
    init(name: String) {
        self.name = name
    }
}

class Address {
    var buildingName: String?
    var building
}

class Residence113 {
    var rooms = [Room113]()
    var numberOfRooms: Int {
        return rooms.count
    }
    subscript(i: Int) -> Room113 {
        return rooms[i]
    }
    func printNumberOfRooms() {
        println("The number of rooms is \(numberOfRooms)")
    }
    var address: Address113?
}

class Person112 {
    var residence: Residence?
}

class Residence {
    var numberOfRooms = 1
}

let john112 = Person112()

if let roomCount = john112.residence?.numberOfRooms {
    println("John's residence has \(roomCount) rooms")
} else {
    println("Unable to retrive the number of rooms.")
}

john112.residence = Residence()


class HTMLElement2 {
    let name: String
    let text: String?
    
    lazy var asHTML: () -> String = {
        [unowned self] in
        if let text = self.text {
            return "<\(self.name)>\(text)</\(self.name)>"
        } else {
            return "<\(self.name) />"
        }
    }
    
    init(name: String, text: String? = nil) {
        self.name = name
        self.text = text
    }
    
    deinit {
        println("\(name) is being deinitialized")
    }
}

var p2: HTMLElement2? = HTMLElement2(name: "p", text: "Hello, world2")
println(p2!.asHTML())
p2 = nil

class HTMLElement {
    let name: String
    let text: String?
    
    lazy var asHTML: () -> String = {
        if let text = self.text {
            return "<\(self.name)>\(text)</\(self.name)>"
        } else {
            return "<\(self.name) />"
        }
    }
    
    init(name: String, text: String? = nil) {
        self.name = name
        self.text = text
    }
    
    deinit {
        println("\(name) is being deinitialzed")
    }
}

var paragraph: HTMLElement? = HTMLElement(name: "p", text: "hello, world")
println(paragraph!.asHTML())


/*
class Country {
    let name: String
    let capitalCity: City!
    
    init(name: String, capitalName: String) {
        self.name = name
        self.capitalCity = City(name: capitalName, country: self)
    }
}

class City {
    let name: String
    unowned let country: Country
    
    init(name: String, country: Country) {
        self.name = name
        self.country = country
    }
}
*/
class Customer {
    let name: String
    var card: CreditCard?
    
    init(name: String) {
        self.name = name
    }
    
    deinit {
        println("\(name) is being deinitialized")
    }
}

class CreditCard {
    let number: Int
    unowned let customer: Customer
    
    init(number: Int, customer: Customer) {
        self.number = number
        self.customer = customer
    }
    
    deinit {
        println("Card #\(number) is being deinitialized")
    }
}

var john: Customer?
john = Customer(name: "John Appleseed")
john!.card = CreditCard(number: 1234_567_999, customer: john!)
john = nil


/*
class Person31 {
    let name: String
    init(name: String) {
        self.name = name
    }
    var apartment: Apartment?
    deinit {
        println("\(name) is being deinitialized")
    }
}

class Apartment {
    let number: Int
    init(number: Int) {
        self.number = number
    }
    
    weak var tenant: Person31?
    
    deinit {
        println("Apartment #\(number) is being deinitialized")
    }
}

var john: Person31?
var number73: Apartment?

john = Person31(name: "John Appleseed")
number73 = Apartment(number: 73)

john!.apartment = number73
number73!.tenant = john

john = nil
number73 = nil

*/
struct Bank {
    static var coinsInBank = 10_000
    static func vendCoins(var numberOfCoinsToVend: Int) -> Int {
        numberOfCoinsToVend = min(numberOfCoinsToVend, coinsInBank)
        coinsInBank -= numberOfCoinsToVend
        return numberOfCoinsToVend
    }
    static func receiveCoins(coins: Int) {
        coinsInBank += coins
    }
}

class Player14 {
    var coinsInPurse: Int
    
    init(coins: Int) {
        coinsInPurse = Bank.vendCoins(coins)
    }
    
    func winCoins(coins: Int) {
        coinsInPurse += Bank.vendCoins(coins)
    }
    
    deinit {
        Bank.receiveCoins(coinsInPurse)
    }
}

var playerOne: Player14? = Player14(coins: 100)
println("A new player has joined the game with \(playerOne!.coinsInPurse) coins")

playerOne!.winCoins(2_000)
println("PlayerOne won 2000 coins & now has \(playerOne!.coinsInPurse) coins")

playerOne = nil
println("PlayerOne has left the game")

/*
struct Checkerboard {
    let boardColors: [Bool] = {
        var temporaryBoard = Bool[]()
        var isBlack = false
        
        for i in 1... 10 {
            for j in 1... 10 {
                temporaryBoad.append(isBlack)
                isBlack = !isBlack
            }
            isBlack = !isBlack
        }
        return temporaryBoard
    }()
    
    func squareIsBlackAtRow(row: Int, column: Int) -> Bool {
        return boardColors[(row * 10) + column]
    }
}
*/
class Food {
    var name: String
    
    init(name: String) {
        self.name = name
    }
    convenience init() {
        self.init(name: "[Unnamed]")
    }
}

let namedMeat = Food(name: "Bacon")
let mysteryMeat = Food()

class RecipleIngredient: Food {
    var quantity: Int
    
    init(name: String, quantity: Int) {
        self.quantity = quantity
        super.init(name: name);
    }
    
    convenience override init(name: String) {
        self.init(name: name, quantity: 1)
    }
}

let oneMysteryItem = RecipleIngredient()
let oneBacon = RecipleIngredient(name: "Bacon")
let sixEggs = RecipleIngredient(name: "Eggs", quantity: 6)

class ShoppingListItem: RecipleIngredient {
    var purchased = false
    var description: String {
        var output = "\(quantity) x \(name.lowercaseString)"
        output += purchased ? " purchased" : " unpurchased"
        return output
    }
}

var breakfastList = [
    ShoppingListItem(),
    ShoppingListItem(name: "Bacon"),
    ShoppingListItem(name: "Eggs", quantity: 6),
]

breakfastList[0].name = "Orange juice"
breakfastList[0].purchased = true

for item in breakfastList {
    println(item.description)
}

struct Size10 {
    var width = 0.0, height = 0.0
}

struct Point10 {
    var x = 0.0, y = 0.0
}

struct Rect {
    var origin = Point10()
    var size = Size10()
    
    init() {
        
    }
    
    init(origin: Point10, size: Size10) {
        self.origin = origin
        self.size = size
    }
    
    init(center: Point10, size: Size10) {
        let originX = center.x - (size.width / 2)
        let originY = center.y - (size.height / 2)
        self.init(origin: Point10(x: originX, y: originY), size: size)
    }
}

let basicRect = Rect()


struct Size {
    var width = 0.0, height = 0.0
}

let twoByTwo = Size(width: 2.0, height: 2.0)

class ShoppingListItem2 {
    var name: String?
    var quantity = 1
    var purchased = false
}

var item = ShoppingListItem()

class SurveryQuestion {
    var text: String
    var response: String?
    
    init(text: String) {
        self.text = text
    }
    func ask() {
        println(text)
    }
}

let cheeseQuestion = SurveryQuestion(text: "Do you like cheese?")
cheeseQuestion.ask()
cheeseQuestion.response = "Yes, I do like cheese"

struct Color5 {
    var red = 0.0, green = 0.0, blue = 0.0
    
    init(red: Double, green: Double, blue: Double) {
        self.red = red
        self.green = green
        self.blue = blue
    }
}

let magenta = Color5(red: 1.0, green: 0.0, blue: 1.0)

struct Fahrenheit {
    var tempearture: Double
    init() {
        tempearture = 32.0
    }
}

var f = Fahrenheit()
println("The default templature is \(f.tempearture)")

struct Celsius {
    var temperatureInCelsius: Double = 0.0
    
    init(fromKelvin kelvin: Double) {
        temperatureInCelsius = kelvin - 273.15
    }

}

let boilingPointOfWater = Celsius(fromKelvin: 212.0)


class Vehicle {
    var numberOfWheels: Int
    var maxPassengers: Int
    
    func description() -> String {
        return "\(numberOfWheels) wheels; up to \(maxPassengers) passengers"
    }
    
    init() {
        numberOfWheels = 0
        maxPassengers = 1
    }
}

let someVehicle = Vehicle()
println(someVehicle.description())

class Bicycle: Vehicle {
    override init() {
        super.init()
        numberOfWheels = 2
    }
}

let bicycle = Bicycle()
println("Bicycle: \(bicycle.description())")


class Car: Vehicle {
    var speed: Double = 0.0
    
    override init() {
        super.init()
        maxPassengers = 5
        numberOfWheels = 4
    }
    
    override func description() -> String {
        return super.description() + "; " + "traveling at \(speed) mph"
    }
}

let car = Car()
println("Car: \(car.description())")

class SpeedLimitedCar: Car {
    override var speed: Double {
        get {
            return super.speed
        }
        set {
            super.speed = min(newValue, 40.0)
        }
    }
}

let limitedCar = SpeedLimitedCar()
limitedCar.speed = 60.0
println("SpeedLimitedCar: \(limitedCar.description())")

class AutomaticCar: Car {
    var gear = 1
    override var speed: Double {
        didSet {
            gear = Int(speed / 10.0) + 1
        }
    }
    override func description() -> String {
        return super.description() + " in gear \(gear)"
    }
}

let automatic = AutomaticCar()
automatic.speed = 35.0
println("AutomaticCar: \(automatic.description())")


struct Matrix {
    let rows: Int, columns: Int
    var grid: [Double]
    
    init(rows: Int, columns: Int) {
        self.rows = rows
        self.columns = columns
        grid = Array(count: rows * columns, repeatedValue: 0.0)
    }
    
    func indexIsValidRow(row: Int, column: Int) -> Bool {
        return row >= 0 && row < rows && column >= 0 && column < columns
    }
    
    subscript(row: Int, column: Int) -> Double {
        get {
            assert(indexIsValidRow(row, column: column), "Index out of range")
            return grid[(row * columns) + column]
        }
        set {
            assert(indexIsValidRow(row, column: column), "Index out of range")
            grid[(row * columns) + column] = newValue
        }
    }
}

var matrix2 = Matrix(rows: 2, columns: 2)
matrix2[0, 1] = 1.5
matrix2[1, 0] = 3.2
for item in matrix2.grid {
    println(item)
}

var numberOfLegs = ["spider": 8, "ant": 6, "cat": 4]
numberOfLegs["bird"] = 2
println(numberOfLegs)

struct TimesTable {
    let multiplier: Int
    subscript(index: Int) -> Int {
        return multiplier * index
    }
}

let threeTimesTable = TimesTable(multiplier: 3)
println("3 的 6倍是\(threeTimesTable[6])")

struct LevelTracker {
    static var heighestUnlockLevel = 1
    static func unlockLevel(level: Int) {
        if level > heighestUnlockLevel {
            heighestUnlockLevel = level
        }
    }
    static func levelIsUnlocked(level: Int) -> Bool {
        return level <= heighestUnlockLevel
    }
    var currentLevel = 1
    mutating func advanceToLevel(level: Int) -> Bool {
        if LevelTracker.levelIsUnlocked(level) {
            currentLevel = level
            return true
        }else {
            return false
        }
    }
}

class Player {
    var tracker = LevelTracker()
    let playerName: String
    func completedLevel(level: Int) {
        LevelTracker.unlockLevel(level + 1)
        tracker.advanceToLevel(level + 1)
    }
    init(name: String){
        playerName = name
    }
}

var player = Player(name: "lnmcc")
player.completedLevel(1)
println("highest unlocked level is now \(LevelTracker.heighestUnlockLevel)")

var player2 = Player(name: "wangsijie")
if player2.tracker.advanceToLevel(6) {
    println("player is now on level 6")
} else {
    println("level 6 has not yet been unlocked")
}

enum TriStateSwitch {
    case Off, Low, High
    mutating func next() {
        switch self {
        case Off:
            self = Low
        case Low:
            self = High
        case High:
            self = Off
        }
    }
}

var ovenLight = TriStateSwitch.Low
ovenLight.next()

/*

struct Point3 {
    var x = 0.0, y = 0.0
    func isToTheRightOfX(x: Double) -> Bool {
        return self.x > x
    }
}
let somePoint = Point3(x: 4.0, y: 5.0)
if somePoint.isToTheRightOfX(1.0) {
    println("This point is to the right of the line where x == 1.0")
}

struct Point2 {
    var x = 0.0, y = 0.0
    mutating func moveByX(deltaX: Double, y deltaY: Double) {
        x += deltaX
        y += deltaY
    }
}

var somePoint2 = Point2(x: 1.0, y: 1.0)
somePoint2.moveByX(2.0, y: 3.0)
println("The point is now at (\(somePoint2.x), \(somePoint2.y))")

struct Point5 {
    var x = 0.0, y = 0.0
    mutating func moveByX(deltaX: Double, y deltaY: Double) {
        self = Point5(x: x + deltaX, y: y + deltaY)
    }
}

class Counter {
    var count = 0
    func incremrnt() {
        count++
    }
    func incrementBy(amount: Int) {
        count += amount
    }
    func reset() {
        count = 0
    }
}

let counter = Counter()
counter.incremrnt()
counter.incrementBy(5)
counter.reset()

struct AudioChannel {
    static let thresholdLevel = 10
    static var maxInputLevelForAllChannels = 0
    var currentLevel: Int = 0 {
        didSet {
            if currentLevel > AudioChannel.thresholdLevel {
                currentLevel = AudioChannel.thresholdLevel
            }
            if currentLevel > AudioChannel.maxInputLevelForAllChannels {
                AudioChannel.maxInputLevelForAllChannels = currentLevel
            }
        }
    }
}

var leftChannel = AudioChannel()
var rightChannel = AudioChannel()

leftChannel.currentLevel = 7
println(leftChannel.currentLevel)
println(AudioChannel.maxInputLevelForAllChannels)

rightChannel.currentLevel = 11
println(rightChannel.currentLevel)
println(AudioChannel.maxInputLevelForAllChannels)

struct SomeStructure {
    static var storedTypeProperty = "Some value."
    static var computeredTypeProperty: Int {
        return 1
    }
}

enum SomeEnumeration {
    static var storedTypeProperty = "Some value."
    static var computeredTypeProperty: Int {
        return 2
    }
}

class SomeClass {
    class var computeredTypeProperty: Int {
        return 3
    }
}

println(SomeClass.computeredTypeProperty)
println(SomeStructure.storedTypeProperty)
SomeStructure.storedTypeProperty = "Another value"
println(SomeStructure.storedTypeProperty)

class StepCounter {
    var totalSteps: Int = 0 {
        willSet(newTotalSteps) {
            println("TotalSteps = \(newTotalSteps)")
        }
        didSet {
            if totalSteps > oldValue {
                println("Added \(totalSteps - oldValue) steps")
            }
        }
    }
}

let stepCounter = StepCounter()
stepCounter.totalSteps = 100
stepCounter.totalSteps = 200
stepCounter.totalSteps = 300

struct Point11 {
    var x = 0.0, y = 0.0
}

struct Size11 {
    var width = 0.0, height = 0.0
}

struct Rect11 {
    var origin = Point11()
    var size = Size11()
    var center: Point {
        get {
            let centerX = origin.x + (size.width / 2)
            let centerY = origin.y + (size.height / 2)
            return Point(x: centerX, y:centerY)
        }
        set(newCenter) {
            origin.x = newCenter.x - (size.width / 2)
            origin.y = newCenter.y - (size.height / 2)
        }
    }
}

var square = Rect(origin: Point11(x: 0.0, y: 0.0), size: Size11(width: 10.0, height: 10.0))
let initialSquareCenter = square.center
square.center = Point(x: 15.0, y: 15.0)
println("Square.origin is now at (\(square.origin.x), \(square.origin.x))")

struct AlternativeRect {
    var origin = Point()
    var size = Size()
    var center: Point {
        get {
            let centerX = origin.x + (size.width / 2)
            let centerY = origin.y + (size.height / 2)
            return Point(x:centerX, y: centerY)
        }
        set {
            origin.x = newValue.x - (size.width / 2)
            origin.y = newValue.y - (size.height / 2)
        }
    }
}

struct Cuboid {
    var width = 0.0, height = 0.0, depth = 0.0
    var volume: Double {
        return width * height * depth
    }
}

let fourByFiveByTwo = Cuboid(width: 4.0, height: 5.0, depth: 2.0)
println("the volumn of fourByFiveByTwo is \(fourByFiveByTwo.volume)")

class DataImporter {
    var fileName = "data.txt"
}

class DataManager {
    lazy var importer = DataImporter()
    var data = [String]()
}

let manager = DataManager()
manager.data.append("Some data")
manager.data.append("Some more data")
println(manager.data)

struct FixedLengthRange {
    var firstValue: Int
    let length: Int
}

var rangeOfThreeItems = FixedLengthRange(firstValue: 0, length: 3)


var names11 = ["Mohsen", "Hilary", "Justyn", "Amy", "Rich"]

var a = [1, 2, 3]
var b = a
var c = a

println(a[0])
println(b[0])
println(c[0])

a[0] = 42

println(a[0])
println(b[0])
println(c[0])

func printArray(array: [Int]) {
    println(array)
}

printArray(a)
printArray(b)
printArray(c)



var ages = ["Peter": 23, "Wei": 35, "Anish": 65, "Katya": 19]
var copiedAges = ages;

println((ages["Peter"]!))

struct Resolution {
    var width = 0
    var height = 0
}

class VideoMode {
    var resolution = Resolution()
    var interlaced = false
    var frameRate = 0.0
    var name: String?
}

let someResolution = Resolution()
let someVideoMode = VideoMode()

println("The width of someResolution is \(someResolution.width)")

let vga = Resolution(width: 640, height: 480);
println("The VGA resolution width is \(vga.width)")

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

*/