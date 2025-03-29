# Individual Route Planning Tool

## Features
- Calculates the shortest route between two nodes of a given graph
- Driving mode (with and without restrictions)
- Driving + Walking mode

## Usage
### Menu Mode:
- Load csv files
    - Place Distances.cvs and Locations.csv in the "csv_files" folder before running the program
- Select mode
- Execute functionality
- Exit

### Batch Mode:
- Place Distances.cvs and Locations.csv in the "csv_files" folder
- Place "input.txt" inside the "Batch_Mode_Files" folder
- Run the program and select Batch Mode
- The output will be written to "output.txt" in the "Batch_Mode_Files" folder

#### input.txt Examples
Please follow the following formatting for the input.txt file

#Test1 (replace Test1 with the name of the test)

Mode:driving

Source:id

Destination:id

AvoidNodes:id,id,... (optional)

AvoidSegments:(id,id),(id,id),... (optional)

IncludeNode:id (optional)

OR

Mode:driving-walking

Source:id

Destination:id

MaxWalkTime:int

AvoidNodes:id,id,... (optional)

AvoidSegments:(id,id),(id,id),... (optional)

