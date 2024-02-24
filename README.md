# Study Contract Application (QT-ContractDeStudii/StudyContract)

This Study Contract Application was developed in C++ with a QT GUI during my Object-Oriented Programming (OOP) course laboratories.

Throughout the development process, spanning several weeks, I acquired a wealth of knowledge about design patterns, memory management, and working with graphical interfaces using QT. In the initial iterations, I even delved into implementing my own vector class. ((can be seen here)[])

## Patterns Learned:

- **Observer pattern**
- **Model View Controller**
  
## Memory Management Techniques:

- **RAII (Resource Acquisition Is Initialization)**
- **Rule of Three (C++)**
- **Rule of Five (C++)**
- **Memory Leak Detection**
- **Handling Dangling Pointers**
- **Smart Pointers**

The application's purpose is to facilitate the creation of subjects for a school entity. Users can filter and sort subjects, and if desired, generate a study contract.

Below are screenshots from the application, accompanied by further details about its functionalities.

Let's take a look at the User Interface:

![Main UI](image.png)
Here, the user can easily sort the subject list and apply filters with utmost convenience.
![Filter Demonstration](image-1.png)

In addition to creating subjects, users can also modify or delete selected subjects. Notably, the application supports undo functionality to rectify inadvertent actions.

For users intent on crafting a study contract, the "Open Contract" button serves as their gateway.
![Contract View](image-2.png)
Upon entering the contract creation view, users are presented with an interactive form showcasing the number of subjects selected. This feature serves as an excellent learning opportunity for observing the Observer pattern in action.
![Subject Display Example](image-3.png)
Furthermore, users can opt to export the contract to an HTML table by specifying a filename and clicking "Export to Contract."
![Filename Entry](image-4.png)
![HTML Contract File](image-5.png)
Feel free to explore the application further!
