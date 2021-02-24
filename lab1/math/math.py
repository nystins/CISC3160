#Formula for Fahrenheit to Celsius
def FtoC(num):
    return  (num-32)/1.8

#Formula for Celsius to Fahrenheit
def CtoF(num):
   return (num*1.8)+32

#User has a choice to go from Fahrenheit to Celsius
def Fstart():
    my_list = user_weather()
    print('\tFahrenheit \t Celsius' )
    print('\tHigh / Low \t High / Low' )
    for i in range(len(my_list)):
        print(f'Day {i+1}:\t{my_list[i][0]} / {my_list[i][1]} \t {FtoC(my_list[i][0])} / {FtoC(my_list[i][1])}')

#User has a choice to go from Celsius to Fahrenheit
def Cstart():
    my_list = user_weather()
    print('\tCelsius \t Fahrenheit' )
    print('\tHigh / Low \t High / Low' )
    for i in range(len(my_list)):
        print(f'Day {i+1}:\t{my_list[i][0]} / {my_list[i][1]} \t {CtoF(my_list[i][0])} / {CtoF(my_list[i][1])}')

def user_weather():
    my_list=[]
    temp_list=[]
    #let user define whether to check for 7 days or 30 days.
    n=int(input('Enter how many days of weather forecast you would like to check: '))
    for i in range(n):  # for number of sub-list in the list
        for j in range(0,2): # range(2) for size of sub_list
            temp_list.append(float(input('Please enter weather for high then low: '))) #allow user to enter their own weather forecast
        my_list.append(temp_list)
        temp_list=[]  #set temp_list to null
        return my_list

def main():
    print(f'1 = Fahrenheit and 2 = Celsius')
    i=int(input('1 or 2 '))
    if(i==1):
        Fstart()
    elif(i==2):
        Cstart()
    else:
        print('Entered the wrong number please re-run program.')

if __name__ == "__main__":
    main()
    