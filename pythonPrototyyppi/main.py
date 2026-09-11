import random
import time
import numpy as np

def start():
    x = True
    while x == True:
        answer = input("Aloitetaanko? (Y/n) ")

        if answer == "y" or answer == "Y":
            # Tähän saa laitettua buzzerin huutamaan startti soundin
            print("Aloitetaan!")
            x = False
        elif answer == "n" or answer == "N":
            print("Kysytään uudestaan. ")
        else: 
            print("Laita (Y/n). ")

def game():
    play_again = True
    score = 0
    increment = 1.5
    sub = 0.3

    while play_again:
        colors = {}

        # Määritellään num1-4 arvot
        for i in range(1, 5):
            colors[f"num{i}"] = random.randint(1, 4)

        # Tulostetaan taulun arvot
        for key, value in colors.items():
            print(f"{value}")
            time.sleep(increment)

        # Itse arvailulogiikka + kokonaistuloksen laskeminen
        for i in range(1, 5):
            try:
                guess = int(input(f"{i}. luku? "))
            except:
                print("Anna kokonaisluku apina \n")
                continue

            if guess == colors[f"num{i}"]:
                # Tähän sais buzzerin huutamaan kun vastaus on oikein
                print("OIKEIN")
                score += 1
            else: 
                # Tähän sais buzzerin huutamaan kun peli hävitään
                print("VÄÄRIN")
                play_again = False
                print("Kokonaistulos: ", score)

        increment = max(0, increment - sub)
        
start()
game()