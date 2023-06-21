# Final Project - Introduction to Robotics
### by Fabian Becker, Florian Remberger & Quang Thanh Lai

## Project Description
The aim of this project is for the robot to make it's way through a predefinied map and navigate to two destinations.

## Task Importing
Simple for loop is necessary to copy characters from string into a 2D array with dimensions 14x14.

## Pathfinding and Route Creation
Dijkstra's Algorithm is used for pathfinding

## Driving Controls

## Individual Contributions
### Fabian Becker (Pathfinding & Route Creation
TODO

### Florian Remberger (Importing & Driving Controls)
## Importing
Importing the map is quite simple. We don't need to read it directly from a text file. 
A const char* variable called mapString is used to store the map string.
It is located in the main.c file. It must be changed manually if you want the robot to use a different map.

The 2D array mapStringMatrix is also declared in main.c and can be filled with the characters from mapString using a simple for-loop.

We need to iterate from i = 0 to i < 196, incrementing i after each loop. This is because the 14x14 map stored in the string contains 196 characters (14 * 14 = 196).
For each character, we must calculate the correct row and column to store in the 2D array.

The row can be determined by dividing i by 14. Due to the datatypes of i (uint8_t) and 14 (int by default), this calculation is evaluated as an integer. 
The result is an integer between 0 and 13, which determines in which row of the array the character at position i in mapString will be stored.

The column is calculated by the operation i % 14. This will also return an integer between 0 and 13 that represents the column of the array.

Using both calculations, we can now combine them to get the following equation.
mapStringMatrix[i/14][i%14] = mapString[i]

## Driving Controls
### function driveTiles(uint8_t tiles) 
This function is located in the motion.c file. 
It makes the robot move forward in a straight line. 
The input parameter tiles represents the number of tiles (each tile has a length of 25 cm) that the robot should move forward. 
Using a 14x14 map, the tiles datatype uint8_t will be sufficient because we cannot move more than 12 tiles before hitting a wall. 

Calculating the distance to travel is the first thing this function does. 
This calculation is quite simple, because we only have to multiply the tiles by 25 (cm) to get the total distance we want to move. We also multiply the already calculated distance by 1000 because we do not want to use floating point values.  

After calculating the distance, we declare two variables. We will use them to calculate the difference in degrees.  

Now we get the current degree of the wheels. We store this value in the prev_deg variable.  

The general logic of this drive function is: 
First we start the motors and then we check how much distance we have traveled since the last check. 
From the total distance we have to travel, we subtract the distance traveled. 
We stop the motors and set Motor_stop_float if the total distance is less than 2cm (represented as 2000 in our code due to the multiplication with 1000 earlier).  
So the first thing inside the while loop has to be a delay. So we do not get the same degree value as just before the while loop. 
We let the motors run for 200ms. So we can be sure that we get a bigger degree value.  
Now that we have the new degree value and have stored it in the deg variable, we need to calculate the distance that the robot has moved. 
This calculation is quite complex. So I want to break it down into smaller steps:

1) **Calculate the difference between the old degree value and the new degree value**. This can be done by subtracting the old value stored in prev_deg from the current degree value stored in deg. In our code we use the function getAbsDiff which calculated the absolute difference so we do not get any negative numbers.
2) **Multiply** the number we just calculated **by 2**. The Motor_Tacho_GetCounter function will return 1 for every two degrees the motor has rotated. 
3) **Divide it by 360.0**. 360 degrees would be a full turn of the motor and therefore a full turn of the wheel. What we want to calculate here is how many times the wheel has turned. The .0 guarantees, that the result will be of type double so we do not lose precision.
4) **Multiply by CIRCUMFERENCE**. CIRCUMFERENCE is the circumference of the wheel. After this step, we now know excactly how many centimeters the robot has moved since the last check. 
5) **Multiply by 1000**. If we did not multiply by 1000, we would lose the decimal places because we are subtracting a double from an int. Because of this step we also had to multiply by 1000 when we first calculated the total distance.

After calculating the distance we can simply subtract it from the total distance and set prev_deg to deg.

This procedure is repeated until the distance is less than or equal to 2cm. 
If this is the case, the motors will stop and the function will end.
### function turn(uint8_t dir)
The motion.c file also contains the funtion turn.
It makes the robot turn left or right according to the input parameter dir.
If dir is equal to 1, the robot will turn left and if dir is equal to 0, the robot will turn right.
We need to declare several variables that will be used later to store
the distance to be covered by the left and right motors (distanceL, distanceR).
To assign these variables we have to calculate the distance that both wheels have to turn. 
We have measured, that the distance between the two wheels is 8 cm.
We also know, that the robot has to turn 90 degrees. 
Using this information we can approximate the distance one wheel has to travel by calculating the circumference for a circle with a diameter of 8 cm. Then we have to multiply the calculated value by 1/4 because the wheels only have to travel 1/4 of the circle.

1/4 * (8 * pi) = 2 * pi

We want to avoid floating-point values so we multiply the result of the above equation by 1000.

After calculating the distance that both wheels have to travel, we declare variables that will store the current degree value of both motors as well as the previous degree values (prev_degL, prev_degR, degL, degR).
Then we define the variables motorL and motorR with 20 which represents the motor force for the left and right motor.

TODO: Definition of variables diffL, diffR, offset.

The next thing this function does is get the current motor degree for the left and right motors and assign that value to the prev_degL and prev_degR variables.

We then start both motors using the ternary operator to evaluate the direction each motor must move using the dir parameter.

The while loop makes sure that each motor travels the distance it has to travel. Therefore, the condition of the while loop will be evaluated as true as long as one of the distances (distanceL or distanceR) is greater than 0.

Inside the while loop we first check if the distanceL variable is less than or equal to 0.
If so, we stop the left motor because we have already moved enough distance on that side.
Else if the distanceL variable is greater than 0, we get the current motor degree and store that value in the degL variable.
Now that we have the previous and current degree value we can calculate the exact distance the wheel has turned since the last check.
This can be done in the following way:
1) Calculate the amount the wheel has turned:
   First we calculate the difference between prev_degL and degL.
   Then we multiply this value by 2 because the motor sensor returns 1 for
   every 2 degrees it turned.
   Dividing this result by 360 gives us the exact amount the wheel has turned.
   ((degL - prev_degL) * 2) / 360

2) Multiply the result by the CIRCUMFERENCE of the wheel:
   By multiplying the amount the wheel turned by the CIRCUMFERENCE of the
   wheel we get the exact distance it traveled.

3) Multiply the result by 1000:
   This must be done because we want to avoid floating point values.

After calculating the distance the wheel has turned we subtract that value from the total distance it has to turn.

The last operation of the else part is to assign the current degree value to the prev_degL variable so that we can do the same calculation steps in the next iteration.

The same procedure is used for the right motor.


### Quang Thanh Lai (Route Creation &  Driving Controls)
TODO


---

