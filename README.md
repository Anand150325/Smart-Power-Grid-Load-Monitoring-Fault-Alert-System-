#                                                                Smart Power Grid Load Monitoring & Fault Alert System

## Overview
This project simulates a **Smart Power Grid Monitoring System** using **C programming and Linux system programming concepts**.  
It models multiple **substations** that generate electrical parameters such as **Voltage, Current, and Load**, and a **central controller** that monitors, analyzes, logs, and generates alerts in real-time.

The system demonstrates:
- Multi-process architecture
- Inter-Process Communication (IPC)
- File handling**
- Real-time monitoring**


##  Objectives
- Simulate **distributed power substations**
- Perform **real-time monitoring**
- Detect abnormal conditions:
  - Overload
  - Low Voltage
- Generate alerts using IPC
- Maintain system logs

## System Components
 1. Substation Processes
- Created using **`fork()`**
- Generate:
  - Voltage (V)
  - Current (I)
  - Load = V × I
- Send data to controller using **Message Queue (`mq_send()`)**



 2. Controller (Central Unit)
- Receives data using **`mq_receive()`**
- Analyzes system conditions:
  - NORMAL
  - LOW VOLTAGE
  - OVERLOAD
- Logs system data into file
- Sends alerts using **Pipe (write())


  3. Alert Process
- Created using fork()
- Receives alerts using read()
- Displays alert messages on terminal
  

4. Logging System
- File: grid_log.txt
- Stores:
  - System status
  - Fault conditions
- Uses file handling:
  - open()
  - write()
  - close()


# IPC Mechanisms Used

| IPC Type        | Usage                          |
|----------------|--------------------------------|
| Message Queue  | Substation → Controller        |
| Pipe           | Controller → Alert Process     |



## Data Flow

Substation → Message Queue → Controller → Pipe → Alert Process  
↓  
Log File (grid_log.txt)


## Functionality

 - Normal Condition
- Displays system status
- Logs data into file

 ## Fault Condition
- Detects:
  - Overload
  - Low Voltage
- Generates alert via pipe
- Logs fault data



## Technologies Used
-  Programming
- Linux System Calls
- POSIX Message Queue
- Pipe (IPC)
- File Handling
- Process Management (fork())


