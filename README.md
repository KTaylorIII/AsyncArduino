# AsyncArduino
A small toolkit for easy, asynchronous square signal output and user input for the Arduino platform.
<h1>What is this?</h1>
AsyncArduino is a set of C/C++ files and associated headers designed to facilitate non-blocking event listeners and responders for
the Arduino ecosystem. Initialization functions build the <strong>button</strong> and <strong>sigl</strong> data structures which keep
track of their states and other information [1]. Appropriate methods for struct processing ensure that multiple concurrent event listeners
are capable of manipulating the Arduino's IO pins with minimal contention. (<strong>Note: This library is <i>not</i> rated for 
real-time applications, nor is it thread-safe!</strong>).
<h2>How do I get started?</h2>
( Note: This tutorial was typed from a Mac OS X machine.)
<ol>
<li>(Optional) Open the Arduino IDE and create & save a new project to a new directory.</li>
<li>Clone or otherwise download & extract this package to your Arduino sketch's directory.</li>
<li>(Re)open the Arduino IDE and open the sketch where you have downloaded the files.</li>
<li>At this point, you should see the AsyncArduino files among the file tabs.</li>
<br><i>Insert image here</li><br>
</ol>
<i>WIP</i>
