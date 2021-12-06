/*
 *  UCF COP3330 Fall 2021 Assignment 6 Solution
 *  Copyright 2021 McGreggor Kennison
 */

#include "std_lib_facilities.h"

/*
 *  comments are either taken directly from the book
 *  or inspired by how the book wrote its comments
 */

// Token class
class Token {
public:
	char kind;      
	double value;   
	string name;    
	Token(char ch) :kind(ch), value(0) { }                  // initialize kind with ch
	Token(char ch, double val) :kind(ch), value(val) { }    // initialize kind and value
    Token(char ch, string n) :kind(ch), name(n) { }         // initialize kind and name
};

// Token_stream class
class Token_stream {
public:
    Token_stream();         // make a Token_stream that reads from cin
	Token get();            // get a Token
    void putback(Token t);  // put a Token back
    void ignore(char c);    // discard characters up to and including a c
private:
	bool full;          // is there a Token in the buffer?
	Token buffer;       // here is where we keep a Token put back using putback()

};

// constructor
Token_stream::Token_stream()
    :full(false), buffer(0) { }  // no Token in buffer

const char let = 'L';           // declaration token
const char con = 'C';           // constant token
const char quit = 'q';          // t.kind==quit means that t is q quit Token
const char print = ';';         // t.kind==print means that t is a print Token
const char number = '8';        // t.kind==number means that t is a number Token
const char name = 'a';          // name token
const char square_root = 's';   // square root token
const char power = 'p';         // power function token
const string declkey = "#";     // declaration keyword
const string conkey = "const";  // constant keyword
const string sqrtkey = "sqrt";  // keyword for square root
const string powkey = "pow";    // keyword for power function
const string quitkey = "exit";  // keyword to quit

// read characters from cin and compose a Token
Token Token_stream::get()
{
	if (full) { // check if we already have a Token ready
        full = false;
        return buffer;
    }

	char ch;
    cin >> ch;

	switch (ch) {
    case print:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
    case '%':
    case '=':
    case ',':
		return Token(ch);   // let each character represent itself
	case '.':   // a floating-point-literal can start with a dot
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':   // numeric literal
	{	cin.putback(ch);    // put digit back into the input stream
		double val;
		cin >> val;         // read a floating-point number
		return Token(number,val);
	}
	default:
		if (isalpha(ch) || ch == '#') {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='_')) s+=ch;
			cin.putback(ch);
            if (s == declkey) return Token(let);            // declaration keyword
            if (s == conkey) return Token(con);             // constant keyword
            if (s == sqrtkey) return Token(square_root);    // square root keyword
            if (s == powkey) return Token(power);           // power function keyword
            if (s == quitkey) return Token(quit);           // quit keyword
			return Token(name,s);
		}
		error("Bad token");
	}
}

// put Token back into Token stream
void Token_stream::putback(Token t)
{
    if (full) error("putback() into full buffer");
    buffer = t;     // copy t to buffer
    full = true;    // buffer is now full
}

// ignore Tokens up to specific kind
void Token_stream::ignore(char c)
// c represents the kind of Token
{
    // first look in buffer:
	if (full && c==buffer.kind) {
		full = false;
		return;
	}
	full = false;

    // now search input:
	char ch = 0;
	while (cin>>ch)
		if (ch==c) return;
}

// type for (name,value) pairs
class Variable {
public:
	string name;
	double value;
    bool is_const;
	Variable(string n, double v, bool b) :name(n), value(v), is_const(b) { }
};

vector<Variable> names;

// return the value of the Variable named s
double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined variable ",s);
}

// set the Variable named s to d
void set_value(string s, double d)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) {
            if (names[i].is_const) error(s," is a constant");
			names[i].value = d;
			return;
		}
	error("set: undefined variable ",s);
}

// is var already in names?
bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

// add (var,val) to names
double define(string s, double val, bool b)
{
    if (is_declared(s)) error(s," declared twice");
    names.push_back(Variable(s,val,b));
    return val;
}

Token_stream ts;        // a Token_stream called ts
double expression();    // declaration so that primary() can call expression()

// deal with parenteses, +, -, pow, sqrt, assignments, and names
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':   // handle '(' expression ')'
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
        return d;
	}
	case '-':
		return - primary();
    case '+':
        return primary();
	case number:
		return t.value; // return the numbers value
    case name:
    {   Token t2 = ts.get();    // check next token
        if (t2.kind == '=') {   // handle name '=' expression
            double d = expression();
            set_value(t.name,d);
            return d;
        }
        else {  // not an assignment
            ts.putback(t2);
            return get_value(t.name);
        }
    }
    case square_root:   // handle 'sqrt(' expression ')'
    {   t = ts.get();
        if (t.kind != '(') error("'(' expected");
        double d = expression();
        if (d < 0) error("Square roots of negative numbers... nope!");
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return sqrt(d);
    }
    case power: // handle 'pow(' expression ',' int ')'
    {   t = ts.get();
        if (t.kind != '(') error("'(' expected");
        double d = expression();
        t = ts.get();
        if (t.kind != ',') error("',' expected");
        t = ts.get();
        if (t.kind != number) error("second argument of 'pow' is not a number");
        int i = int(t.value);
        if (i != t.value) error("second argument of 'pow' is not an integer");
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return pow(d,i);
    }
	default:
		error("primary expected");
	}
}

// deal with *, /, %
double term()
{
	double left = primary();
    Token t = ts.get(); // get next token from the Token stream

	while (true) {
		switch(t.kind) {
		case '*':
			left *= primary();
            t = ts.get();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
            t = ts.get();
			break;
		}
        case '%': // i opted for fmod here rather than the pure integer modulo
        {   double d = primary();
            if (d == 0) error("divide by zero");
            left = fmod(left,d);
            t = ts.get();
            break;

        }
		default:
			ts.putback(t);  // put t back into Token stream
			return left;
		}
	}
}

// deal with +, -, =
double expression()
{
	double left = term();   // read and evaluate a Term
    Token t = ts.get();     // get the next Token from the Token stream

	while (true) {
		switch(t.kind) {
		case '+':
			left += term(); // evaluate Term and add
            t = ts.get();
			break;
		case '-':
			left -= term(); // evaluate Term and subtract
            t = ts.get();
			break;
        case '=':
            error("use of '=' outside of a declaration");
		default:
			ts.putback(t);  // put t back into the token stream
			return left;    // finally: no more + or -; return the answer
		}
	}
}

// assume we have seen "let" or "const"
// handle: name = expression
// declare a variable or constant called "name" with the initial value "expression"
double declaration(bool b)
{
	Token t = ts.get();
	if (t.kind != name) error ("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ",var_name);

	double d = expression();
    define(var_name,d,b);
	return d;
}

// handles declarations and expressions
double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration(false);
    case con:
        return declaration(true);
	default:
		ts.putback(t);
		return expression();
	}
}

// clean input after error
void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result

// expression evaluation loop
void calculate()
{
	while (cin)
    try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get(); // first discard all "prints"
            
        if (t.kind == quit) return; // quit
        ts.putback(t);
        cout << result << statement() << endl;
        
	}
	catch(exception& e) {
		cerr << e.what() << endl;   // write error message
		clean_up_mess();
	}
}

int main()
try
{
    // predefine names:
    define("pi",3.1415926535,true);
    define("e",2.7182818284,true);
    define("k",1000,true); // also incorportated drill so k is here

	calculate();

    keep_window_open(); // cope with Windows console mode
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin>>c && c!=';') ;
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin>>c && c!=';');
	return 2;
}