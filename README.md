# This tool is going to provide information about the files that can be very useful in compiling and testing. In this project we are going to focus on discovering cycles and strong components in a given set of files.
A cycle or circular reference is a very poor design decision, when not handled properly and potentially removed, will always cause compilation errors. Most compilers do not check for circular references. So this will be valuable information to show the user to understand why the code does not compile. http://stackoverflow.com/questions/625799/resolve-header-include-circular- dependencies
Strong components on the other hand give information about the testing coverage. Dependencies between software files are essential. However, dependencies complicate process of making changes and excessive dependency degrades flexibility. A strong component indicates that a change may cause new changes in all other files in the same strong component.
