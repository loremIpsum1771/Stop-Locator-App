###Abstract 
***This app can be used to help users to navigate the New York City Subway System. The app enables users to find the nearest NYC subway stop to their current location, find optimized ways of transferring to other trains on various routes, find the shortest route between the train stop they are currently at and any other stop, etc...***

##Features
* **Reads in files for NYC MTA train stops and transfers from MTA website** 
* **Implements shortest path algorithm (BFS) to find distances between locations**
* **Computes distances using lattitude and longitudinal coordinates**

  ###Menu Options
  1. **Print out the information about all the train stops on a specific train route**
  2. **Print out the information about a specific train stop**
  3. **Print out all the train stops within a certain distance**
  4. **Print out the available transfers at a specific train stop**
  5. **Print transfers available at all stops**
  6. **Print out the shortest path length from the current stop to every other stop**
  7. **Print out the shortest path between two stops**
  8. **Find the closest stop to current location and then print the shortest path between that stop and the next closest stop**

###Example Use Case:
* **Your current location is: New York City, NY 42 street and park ave**
* **You choose menu option #8 to find the train stop nearest to your current location**

  **prompt:**   ``` Enter a lattitude, and a longitude```
  
  (The coordinates can be found by using a site like [this one](http://www.latlong.net/))
  
       
  **input:**
  <pre><code>40.752162
  -73.977802
  </code></pre>
                 
  **output:**   
  <pre><code>Destination 631
  distance: 0
  shortest path: 631
  </code></pre>
 
  * *This means that the nearest stop to the current location is 631 which is the stop number for Grand Central Terminal*

  * *This can be confirmed by using menu option 2:*
  
    **prompt:** ```Enter a stop id```
    
    **input:** ```631```
    
    **output:** ``` Grand Central - 42 St 631```
    
  * ***This can be further verified by checking the coordinates using google maps:***
  
    ![alt tag](https://cloud.githubusercontent.com/assets/8988459/9702200/556d2f34-5421-11e5-887e-bb289dd97a38.png)
    
  
