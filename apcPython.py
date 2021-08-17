##  Author: Adam Conger
##  CS 210 SNHU
##
##  This program takes input from a text file and loads each unique word into a vector.
##  It also initializes a respective vector for that word's occurrence in the list input.
##  The menu allows the user to choose between several actions.


import re
import string
uniqueWordList = []
uniqueValueList = []

def append_word(unique_word):
    uniqueWordList.append(unique_word)

def append_value(unique_value):
    uniqueValueList.append(unique_value)

def get_occurrence():
    print(user_input + " was purchased " + v + "times.")
    return 1 ##confirms program submission

def get_individual_occurrence(user_input):
    for i in range(len(uniqueWordList)):
        if user_input == uniqueWordList[i]:
            print("{} was purchased {} times".format(uniqueWordList[i], uniqueValueList[i]))
            break