#Imp Points

##During Calibration

First ensure power supply to ESC is off, then upload arduino code to the board and then turn on the ESC's 12V power supply so that the first thing that hits the ESC is a 2000 pwm signal as 
indicated in the .ino file

##During Logging data

You will face issues with saving the logs as a csv if the order of launching files aren't strictly followed since only one application (either laptop or arduino can access the port at the 
time **not both**

The following steps ensure you get the log file as a _.csv_ smoothly:

1. Delete any previous .csv files saved in the location
2. **Do not ** run the python files before hand (but keep the code for **logger.py** open since the code has like a 5-10 second window before it starts logging)
3. Plug in arduino first, and then turn on the power supply (12V) for the ESC
4. Upload the Project code, **DO NOT open the serial monitor at all**.
5. Once the code says uploaded, go to your python file and then run it
6. It will start logging the data from the port

_If it states an error due to busy port or port already under use_, this means you've either somehow activated the serial monitor or some other application is using the port.
Following above steps ensures the port is free and the data is directly fed into the logger.py file and saved as a csv.

Once your csv is saved, the optional plotter file makes it a plot (**please `pip install seaborn` on your terminal to get the graph accurately or comment out `sns.set_style("darkgrid")` 
and `import seaborn as sns` and uncomment `#plt.style.use("ggplot")` to get the plot working **)

Thank You
