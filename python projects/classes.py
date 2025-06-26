class Person:
    def __init__(self,name):
        self.name = name
    def speak(self):
        return f"my name is: {self.name}"
class Superhero(Person):
    def __init__(self,name,power,inteligence_quotient,bmi,weight,age):
        super().__init__(name)
        self.power = power
        self.inteligence_quotient = inteligence_quotient
        self.bmi = bmi
        self.weight = weight
        self.age = age
    # def speak(self,phrase):
    #     return f"my name is: {self.name}, phrase: {phrase}"
    def __str__(self):
        return f"name: {self.name},IQ: {self.inteligence_quotient},bmi: {self.bmi}"
superman_is_dumb = Superhero("superman","flight,laser eyes,superstrength",30,"27.4(overweight >:D)","225(overweight)","E = 21^infinty(126353625)")
Brad_Ward = Person("Brad Ward")
print(superman_is_dumb.speak())
iron_man = Superhero("Iron Man","his mind",312,"29.2(worse than superman)",225,50)
print(iron_man)
class Animal:
    alive = True
    def __init__(self,weight,height,age,type):
        self.weight = weight
        self.height = height
        self.age = age
        self.type = type
    def sprint(self):
        return f"the {self.type} is sprinting very fast"
class Dog_better_than_cat_L_ratio(Animal):
    def __init__(self,weight,height,age,type,long_ears):
        super().__init__(weight,height,age,type)
        self.long_ears = long_ears
    def sprint(self):
        return f"the doggo is sprinting very hastely"
sloth = Animal(59,"2ft",100101010,"sloth")
print(sloth.sprint())
golden_retriever = Dog_better_than_cat_L_ratio(76972349769876769876,976765672497823497234798723498,38907245234789,"Golden Retriever",True)
print(golden_retriever.sprint())