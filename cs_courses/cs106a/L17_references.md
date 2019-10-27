======================================================================
# LESSON 17.
======================================================================

# REFERENCE SEMANTICS
======================================================================

public void run() {
  int[] pw = new int[4];
  fillWithRandomDigits(pw);
  println(Arrays.toString(pw));
}

Java objects are stored as references
======================================================================
if two variables store the same object, they share that object's data
'
BankAccount ba1 = new BankAccount("Marty", 1.00);
BankAccount ba2 = new BankAccount("Keith", 3.14);
BankAccount ba3 = ba1;

ba3.deposit(4.00);
println(ba1);         // Marty $5.00
println(ba3);         // Marty $5.00

ba1.deposit(2.00);
println(ba1);         // Marty $7.00
println(ba3);         // Marty $7.00

# ARRAY OF OBJECTS.
======================================================================

BA[] accnts = new BA[3] // [ null, null, null]

accnts[0] = new BA("me" , 2);
accnts[1] = new BA("him", 3);
accnts[2] = new BA("her", 4);

# REFERENCE TO SWITCH PAIRS
======================================================================
//                     0   1     2      3       4
String[] names = {"ash","joe","tim", "mike", "bob"};
switchPairs(names);

public void switchPairs(String[] s) {
  for(int i = 0; i < s.length-1; i+=2){
    // swap i with i+1
    String tmp = s[i];
    s[i]   = s[i+1];
    s[i+1] = tmp;
  }
}
