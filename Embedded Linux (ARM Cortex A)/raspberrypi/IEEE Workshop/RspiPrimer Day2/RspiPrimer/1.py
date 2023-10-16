user_name=raw_input("what is u r name?")
print"Welcome to the program",user_name
goagain=1
while goagain==1:
 firstnumber=int(raw_input("type u r first number:"))
 secondnumber=int(raw_input("type u r second number:"))
 print firstnumber,"added to", secondnumber,"equals",
 firstnumber+secondnumber
 print firstnumber,"minus", secondnumber,"equals",
 firstnumber-secondnumber
 print firstnumber, "multiplied by", secondnumber, "equals",
 firstnumber * secondnumber
goagain = int(raw_input("Type 1 to enter more numbers, or any other number to quit: "))
