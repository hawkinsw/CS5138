# CS5138: Malware Analysis

## Course Overview/Introduction
Sherlock Holmes. The Hardy Boys. Nancy Drew. Veronica Mars. Temperance Brennan. Angela Lansbury. Columbo. [Nash Bridges](http://web.archive.org/web/19980116201338/http://www.thenetshow.com/). This is just a short list of the smartest, most astute detectives that the literary world has ever conjured. They are perceptive, daring, logical, persistent and clever. 

Are you sitting down? By the time you complete this course, you will be the Veronica Mars of malware, the Nancy Drew of the digital, the Temperance Brennan of the binary, the Columbo of cyberspace or the Angela Lansbury of, well, the LAN.

This course will teach you the strategy and the tactics for analyzing malware with the ultimate goal of being able to disrupt its harm. The vocabulary, tools, and techniques that you learn during the semester will give you the skills to *safely* analyze an unknown piece of malware and determine:

1. Its intent

2. Its strategy for achieving its intent, and

3. Its tactics for carrying out its strategy. 

Once you know those facts about any malware, disabling it is much easier!

Get ready for an enjoyable and fun ride on the roller coaster of malware analysis where the struggle of frustratingly precise analysis gives way to moments of euphoria when you least expect it!

## Catalog Information 

### Goals
 	
1. Introduction: Definition, Classification, Using Isolated Environments (VMs) - Students will learn the types of malware and the basics of the tools used for reverse engineering. 
2. Intel x86 Architecture: Instruction Set, Memory, Calling Conventions - Students will perform a low level analysis of those instructions including memory and register usage, and calling conventions for subroutines and libraries.
3. C in Assembly: Variables, Stack Usage, Structs, Optimizations - the students will learn what common C programming constructs look like in compiled assembly code. 
4. Intent: History, Identify Purpose, Network Analysis - These topics focus on how to identify the intent of a malware program.
5. Overview of Windows: APIs, Processes and Threads, Network - Students will learn techniques for identifying malware actions by looking at how the code utilizes the operating system's application programming interfaces, process handling, and network connectivity. 
6. Anti-RE: Obfuscation, Packers, Detection of RE - Students will learn how modern malware executables use different techniques to hide code. 

## Time and place
Tuesday, Thursday

6:00pm - 7:20pm

(*Note*: Spring Break will interfere with the normal class schedule. When the University is closed, we will not have class -- obviously!) 

For in-person sections:
RECCENTR 3200

For virtual sections: 
[See course Canvas page -- no Zoombombing allowed](#)

## Class Leaders

### Professor

Will Hawkins

he/him/his

[hawkinwh@ucmail.uc.edu](hawkinwh@ucmail.uc.edu)

864-386-2286

I am a geek. I love computers and puns, not necessarily in that order. I have a silly sense of humor. I am from Cincinnati and have lived in South Carolina; Washington, DC; Virginia; Illinois, and Toronto. I have traveled for work to three continents. I am a sucker for soft pretzels, big salads, coffee and wraps. My favorite restaurant is Lebos (after Chilis, of course).

I love Mercedes AMGs and I just bought my dream car, a Toyota Camry hybrid. Before the start of the semester I bought an aquarium. I enjoy baking -- pretty much anything, but I just made bagels for the first time in my life. The only show I have ever watched on Netflix is Seinfeld. For real.

I also love reading. I like non-fiction more than I like fiction but my favorite writer of all time is David Foster Wallace. I read the Wall Street Journal in print every day and cannot live without my Kindle.

My favorite artist is Andy Warhol and my favorite architect is Frank Lloyd Wright.

Of course, I love sports, too! My favorite basketball team is the Sacramento Kings (as of only a few weeks ago!). My favorite hockey team is the Washington Capitals. My favorite F1 driver is Fernando Alonso and my favorite NASCAR driver is Ross Chastain. Sports are better on radio than they are on TV.

In high school I was a golfer and a basketball player. In college I got in to running and cycling. I think that I am going to start doing CrossFit.

And, crosswords!

### Teaching Assistant
TBD

## Our Hours
### Scheduled
M/W/F 

12:00pm - 1:00pm 

804B Rhodes

There *is* an online option for the Our Hours -- see the course's Canvas page.

### Impromptu

ANYTIME

Just call me, send email or text message, use a [carrier pigeon](https://en.wikipedia.org/wiki/Homing_pigeon) or [smoke flare](https://www.boatus.org/distress-signals/) and I will be happy to meet! Nothing is more important to me than your success in this course!

## Prerequisites
 	
According to the course catalog, to take this course you must be at least a third-year engineering student. The real prerequisite is a desire to learn -- malware analysis is not a subject to master. Malware analysis is a combination of art and science that demands its practitioner to constantly learn the latest tricks that attackers are using to exploit vulnerable systems.

If you have taken some combination of
- CS3003 (Programming Languages),

- CS4065 (Computer Networks and Networked Computing),

- EECE3026 (Introduction to Computer Architecture & Organization), or

- EECE4029 (Operating Systems & Systems Programming)
then you are adequately prepared to succeed in this course!

## Course Format
This is a blended course. Some of the students will be here in person and others will be attending remotely. There will likely be some technical difficulties as we get the mix correct, but I know that everything will work out.

Assessment of your performance will be done through quizzes, assignments and tests. You will benefit from attending the lectures. See Participation below for additional information about the attendance policy. 

## Course Resources
There is no single required textbook for this course. There are, however, books that we will use throughout the semester. These books are accessible electronically through the UC Library system. When readings from these books are assigned, you will be responsible for getting access to the material *legally*:

1. Sikorski, Michael, and Andrew Hoenig. *Practical Malware Analysis*. Boston, MA, No Starch Press, February, 2012. [UC Library Link](http://uclid.uc.edu/record=b8323014~S39)

2. Andriesse, Dennis. *Practical Binary Analysis*. Boston, MA, No Starch Press, December, 2018. [UC Library Link](http://uclid.uc.edu/record=b8342531~S39)

3. Graham, Daniel. *Ethical Hacking*. Boston, MA, No Starch Press, September, 2021. [UC Library Link](http://uclid.uc.edu/record=b8594891~S39)

Besides the texts listed above and the Canvas page for this course, there are two other resources that we will use for this course:

1. A class `git` repository (and associated resources on GitHub like a Wiki, Issue tracker, etc.): [https://github.com/hawkinsw/CS5138](https://github.com/hawkinsw/CS5138). Readings, source code samples, and other materials for this class will be posted in this repository. If you are unfamiliar with `git`, please let me know -- I'll be happy to introduce you!

2. A class Discord server: [LINK](#). You are not required to join this server, but I hope that it will be a place where you can discuss the course with your peers and help one another. Remember, all discussions must be respectful and professional -- see below under _Class Expectations_ for more information.

## Course Outline

### Module 1: Introduction to Malware Analysis and Virtual Machines
By the end of Module 1 you will be able to 
 
- define malware analysis

- describe the importance of malware analysis

- run a guest operating system on your host in a virtualized environment. 

### Module 2: Basic Static Analysis
By the end of Module 2, you will be able to

- understand the value of static analysis in the overall malware analysis process

- describe the characteristics of malware that can be deduced from static analysis

- use various tools to perform basic static analysis of a piece of malware of unknown origin

- write a tool that performs a very straightforward form of static analysis

### Module 3: Basic Dynamic Analysis
By the end of Module 3, you will be able to

- understand the value of dynamic analysis in the overall malware analysis process

- describe the characteristics of malware that can be deduced from dynamic analysis

- use various line tools to perform basic dynamic analysis of a piece of malware of unknown origin

- write a tool that performs a fairly sophisticated form of dynamic analysis on the Windows platform.

### Module 4: Network Analysis
By the end of Module 4, you will be able to

- understand the value of network monitoring and packet analysis in the overall malware analysis process

- describe the characteristics of malware that can be deduced from observing how a piece of unknown malware uses the network

- use various tools to perform network analysis of a piece of malware of unknown origin.

### Module 5: Disassembly
By the end of Module 5, you will be able to

- understand the importance of having the knowledge to disassemble a potentially malicious program (on X86 and ARM platforms) in the overall malware analysis process

- recognize the common machine-code patterns that the compiler emits for common constructs in higher-level programming languages (loops, function calls, switch statements, etc)

- evaluate the behavior of a piece of malware as it executes

- use tools to statically disassemble a piece of malware of unknown origin and dynamically monitor the malware's execution. 

### Module 6: Malware Obfuscation
By the end of Module 6, you will be able to 

- recognize the common tactics that malware authors use to make analysis of their wares more difficult

- overcome those hurdles through static and dynamic malware analysis

### Module 7: Putting It All Together
By the end of Module 7, you will be able to 

- combine static, dynamic and network analysis to decipher the intent of an unknown malicious program

- combine static, dynamic and network analysis to decipher the strategy of an unknown malicious program to achieve its intent

- combine static, dynamic and network analysis to create a plan that will contain, eradicate and recover from an attack. 

## Class Expectations

1. We will learn from one another -- I will learn from you and you will learn from me.

1. The classroom will be a place where everyone is welcome.

1. You will ask questions *when* you have them. You will raise your hand and interrupt me! Every question will be answered; if I cannot answer a question on the spot, I promise to find the answer. 

1. I will not pretend to know everything.

1. We will all try our best.

## Course Requirements

### Canvas
Please check this course's Canvas page and GitHub repository every day. I will use Canvas to make class-wide announcements. I will assume that you read every announcement completely and you will be responsible for any information contained in those messages.

### Reading
Each module will have assigned readings. All reading assignments will be posted on Canvas. Readings will come from external sources or textbooks that you can access for free through the UC library.

### Assignments
There will be 4 assignments throughout the semester. The assignments will be worth 30% of your final grade. For each day that you are late submitting an assignment, you will lose 10%. 

### Participation
Participation will count for 40% of your final grade. One quarter (25%) of your participation grade will be based on your in-class participation. You will receive full credit for in-class participation if you
- Have no more than three (3) unexcused absences during the semester, and
- Actively engage in classroom discussion by asking questions and respectfully engaging with your peers.

The other three quarters (75%) of your participation grade will be based on your work on "mini assignments". These assignments will consist of things like configuring virtual machines on your personal computers, participating in online discussions, practicing using the tools that we learn during lecture, etc. These mini assignments will not require the same level of effort as the regular class assignments. However, your completion of these assignments is crucial for your success in this course.

If you complete the mini-assignments satisfactorily you will receive 100% of the points for the Mini-assignment Participation. If you _mostly_ complete the mini-assignments satisfactorily you will receive 90% of the points for Mini-assignment Participation. If you _occasionally_ complete the mini assignments satisfactorily you will receive half the points for Mini-assignment Participation. If you _do not complete any_ mini assignments satisfactorily, you will receive no points for Mini-assignment Participation.  

### Projects
There will be a midterm and a final project. The projects are worth 30% of your final grade. The theme of the final project will be the same for the undergraduate and graduate students, however the scope will be different. All midterm projects will be due on Friday, March 10th at 11:59pm. All final projects will be due on April 21st at 11:59pm. There will be no late submissions accepted for final projects without prior authorization. 

### Malware Magazine (Extra Credit)
There is one opportunity for extra credit! More information forthcoming.

## Final Grades
According to the percentages above, your grade will be be calculated in Canvas. There will be no +s or -s assigned in this course. Letter grades will be assigned according to the following limits:

| Letter Grade | Percentage Range |
|------------- | -----------------|
| A | 100 - 90|
| B | 89 - 80 |
| C | 79 - 70 |
| D | 69 - 60 |
| F | Below 60|

## Logistics
### Your Success
Your success in this course is my highest priority. I will present the material the best way that I can but I realize that not everyone learns the same way. If you are having trouble with anything in this course, please contact me. You can reach me in my office or via email/cell phone (all contact information is given above). 

Further, I understand that there are reasons why materials I present and distribute may be inaccessible for certain people. I have tried as hard as possible to make each presentation, document, handout, etc. as accessible as possible but if there is anything I can do to help you use the materials, please let me know. 
 
### Class Cancellation
In the event that I have to cancel class, I will post an announcement to the course page on Canvas. 

### Diversity, Equity and Inclusion
Every person who steps foot in this classroom should feel comfortable being their authentic self. Any behavior that threatens that will not be tolerated.

I am committed to the fundamental principles of academic freedom and human dignity. Diversity in all forms is something I welcome, foster, and prize. I believe that honest attempts to understand the perspectives of others facilitates learning, and as a class we will strive to achieve this goal at all times. I strongly disavow discrimination -- including harassment -- on the basis of race, national or ethnic origin, religion, sex or gender identity, disability, age, sexual orientation, or veteran status. I expect that each of us will hold one another accountable for maintaining these ideals.
 
### Personal Care
College is stressful and stress is harmful. In addition, we are learning amid a global pandemic. 

**Your health is a priority.** 

If you feel sick, please stay home. If you feel overwhelmed, contact a care provider. If there is anything I can do to help, please let me know. 

While you are sick, if you are able, please contact me and let me know. However, if you are not able to contact me, *do not worry*. Contact me when you are safe and healthy and we will work out alternate arrangements for anything that you might have missed. There is nothing about this course that we cannot rearrange to accommodate your health and well being.  

### Academic Integrity
Your work is your work. Learning to collaborate is an important part of being a professional. You will be expected to collaborate effectively with your colleagues as a professional. In this course you will have opportunities to work alone and work together. In the description of each quiz, assignment and test you will be given explicit instructions on the collaboration policy. If you have any doubt about what constitutes appropriate collaboration, please contact me immediately. I will gladly answer any questions that you have! You may also want to read the University's [Student Code of Conduct](https://www.uc.edu/campus-life/conduct/student-code-of-conduct.html).

You are free to reference outside materials while completing the assignments (and *only* the assignments). Any materials that you use, however, must be appropriately cited. For programming assignments appropriate citation can be done in comments. For written assignments, appropriate citation can be done using any academic citation format. If you need help learning how to cite resources in written work, I would be glad to help! If you prefer, the professionals in the [Academic Writing Center](https://www.uc.edu/campus-life/learning-commons/programs/writing-center.html) can help you, too.  
 
### Student Resources
The University has a tremendous array of support options for you! If you are comfortable, I will gladly help you find the proper resource. If you are not comfortable talking to me, please visit Student Affairs [online](https://www.uc.edu/campus-life/student-affairs.html) or in person (Steger Student Life Center, Suite 630). 

In case of an emergency, Student Affairs offers a 24-Hour Consultation Crisis Helpline at 513-556-0648. 

### Disability and Accessibility

Students with disabilities have the right to full and equal access at the University of Cincinnati. The [Accessibility Resources (AR)](https://www.uc.edu/campus-life/accessibility-resources.html) office on campus will work with you and me to identify reasonable accommodations to ensure an equitable opportunity to meet all requirements for your course. AR is also a resource for coordinating access and accommodation to all non-academic programs and opportunities available to UC students and potential students.

If you are in need of accommodation, please contact the AR as soon as possible. We will work with them and with you to provide an inclusive and equitable environment for you to learn.

# Current State
This syllabus is current as of 1/9/2023. It is, however, a _living document_ and I reserve the right to change it at any time.