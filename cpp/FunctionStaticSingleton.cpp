class Singleton1 {
	Singleton1() {}
public:
	static Singleton1 &ref() {
		static Singleton1 single;
		return single;
	}
};

class Singleton2 {
	Singleton1 &s1;
	Singleton2(Singleton1 &s) : s1(s) {}
public:
	static Singleton2 &ref() {
		static Singleton2 single(Singleton1::ref());
		return single;
	}
	Singleton1 &f() { return s1; }
};

int main() {
	Singleton1 &s1 = Singleton2::ref().f();
}
