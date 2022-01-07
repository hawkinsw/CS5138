## Malware Analysis Week 1 Notes

_Note_: There are significant parts of these notes that were inspired by [NIST's Guide to Malware Incident Prevention and Handling for Desktops and Laptops](https://github.com/hawkinsw/CS5138/blob/main/Readings/Introduction/NIST800-83%20Guide%20to%20Malware%20Incident%20Prevention%20and%20Handling%20for%20Desktops%20and%20Laptops.pdf) and *Practical Malware Analysis*. I do not claim that all unattributed material is my own creation. 

### Definition of Malware
1. "Process of understanding the behavior and purpose of a suspicious file or URL." [Crowdstrike](https://www.crowdstrike.com/cybersecurity-101/malware/malware-analysis/).
1. "art of dissecting malware to understand how it works, how to identify it and how to defeat/eliminate it." *Practical Malware Analysis*
1. "The study of malware's behavior. The objective of malware analysis is to understand the working of malware and how to detect and eliminate it." *Learning Malware Analysis*

### The Purpose of Malware Analysis

It plays a role in ...

#### Malware Incident Prevention
How? Well, there are 5 different parts of malware incident prevention: policy, awareness, vulnerability mitigation, threat mitigation and defensive architecture:

Malware analysis plays a role in 4 of those 5:

- awareness: Without an analysis of current and historical malware, it's impossible to fully understand malware's "power" and hackers' techniques. Without that understanding, you cannot fully stress malware's prevalence to those you are trying to protect. You analysis of malware also helps persuade users that they are _the key_ to preventing malware through their behavior. 

- vulnerability mitigation: Without analyzing current and historical malware, it's impossible to fully understand the techniques that attackers commonly employ. If you don't know common malware techniques and tactics, it is impossible to design appropriate vulnerability mitigation strategies. For instance, making users turn off their monitors at night is not an effective vulnerability mitigation technique if attackers never use vulnerable "displays" (whatever that might mean!) to launch a strike. However, making users disable their host's unneeded network services is a good vulnerability mitigation technique if you know through analysis that these services often contain exploitable defects.

- threat mitigation: The more you know about previous malware, the easier it is for you to quickly understand new pieces of malware (in other words, threats) and to rapidly deploy *effective* mitigation.

- defensive architecture: (see above). You must know how malware works if you want to build/design effective measures/protocols that will thwart its attacks.

#### Malware Incident Response (IR)

There are four steps to IR: Preparation; Detection and Analysis; Containment, Eradication & Recovery; and Post-Incident Activity. 

1. Detect.
- There are two types of detection: Active and forensic. In _active detection_, the analyst detects resources being attacked as they are being infected using real-time data. In _forensic detection_, the analyst detects all resources that were ever infected by looking for evidence of infection. Are these equally as important?

- The ability to analyze malware is a prerequisite for writing automated tools that can do active or forensic detection. How so? By looking at a piece of malware's _indicators of compromise_ (IOCs). IOCS are "... a forensic artifact or remnant of an intrusion that can be identified on a host or network". [RSA](https://web.archive.org/web/20170914034202/https://blogs.rsa.com/understanding-indicators-of-compromise-ioc-part-i/) 

- Malware analysis makes it possible to understand the full scope of a piece of malware's impact and helps analysts prioritize resource allotment in the face of constrained human and fiscal resources amid multiple ongoing threats. _Note_: _Terminology_ plays an important role here: Analysts use industry-standard terminology to work with other professionals, share intelligence and define priorities.

- Common tools are not always up to the task of detection. For instance, certain malware infections may not be detected by antivirus (AV) software. The malware may be too new (not yet included in AV software) or too targeted (won't ever be included in AV software) for the AV software to function adequately. Only your own analysis of the malware will enable detection.

2. Containment, Eradication & Recovery
- You cannot stop something from spreading unless you know how it spreads. In other words, you must be able to answer the question, "What are the vulnerabilities that this malware exploits?" To determine that answer, you must ... that's right, analyze malware! 
- You cannot contain the malware's damage unless you know how it is performing its damage! For instance, is the malware exfiltrating data? Well, you can't keep it from leaking data unless you know *how* it is leaking that data.
- Can you eradicate something when you do not understand the mechanism that it uses to spread? Install itself? Hide? Unless you know the answers to these questions, you cannot you be sure that you have completely cleaned a host or network!
- Can you recover from a malware attack/infection unless you know *how* the malware harmed you? For example, do you have any hope of recovering kidnapped files if you do not know the ransomware's encryption mechanism?

### Types of Malware

Broadly speaking, there are two types of malware: _mass_ or _targeted_. Mass malware aims at the lowest-common denominator that puts as many hosts/networks in danger as possible. It is "usually ... less sophisticated [than targeted malware] and easier to detect and defend against ..." *Practical Malware Analysis* Targeted malware is like tailored clothing -- specifically designed and fitted for a particular entity. "Without a detailed analysis of targeted malware, it is nearly impossible to protect your network against [targeted] malware and to remove infections. Targeted malware is usually very sophisticated, and your analysis will often require the advanced analysis skills covered in this [class]." *Practical Malware Analysis*

#### Ransomware
"Ransomware is a blanket term used to describe a class of malware that is used to digitally extort victims into payment of a specific fee." *Ransomware*

... 

"The two major forms of ransomware are those that encrypt, obfuscate, or deny access to files, and those that restrict access or lock users out of the systems themselves." *Ransomware*

#### Fileless
Fileless malware is malware whose contents are never actually written to disk. The malware exists only in memory and while it is executing. Adapted from *Preventing Malware*

The category also contains malware that leverages otherwise non-malicious programs that exist on the host/network to do its dirty work. This attack technique is known as _living off the land_. AV vendors cannot add these usually benign programs to their software because they are notionally harmless. Flagging the execution of these binaries will result in having too many false-positives and cause fatigue for the user.

#### Spyware (InfoStealers)
Spyware or InfoStealers spy on and steal sensitive data from a host/network. The data targeted by spyware can be usernames, passwords, images, and documents. Adapted from *Malware Analysis and Detection Engineering*

See also _keyloggers_.

#### Adware (scareware)

Adware and scareware are like Trojans because they are intentionally installed by a user but do not perform as advertised. 

Adware has additional "features" beyond the explicit utility of the program. The feature is to display ads to the user. Adapted from *Malware Analysis and Detection Engineering*

I consider scareware to be a type of adware. It is designed to trick the user into downloading/buying another program by inducing fear. E.g., scareware may induce a user to buy AV software by falsely claiming their system/network is infected by a virus.

#### Trojans
Malicious software designed to look like benign that lures users into installing it voluntarily.

"A Trojan horse is a computer program that is hiding a virus or other potentially damaging program. A Trojan horse can be a program that purports to do one action when, in fact, it is performing a malicious action on your computer. Trojan horses can be included in software that you download for free or as attachments in email messages." [CISA.gov](https://www.cisa.gov/uscert/publications/virus-basics)

"A Trojan horse is a self-contained, nonreplicating program that, while appearing to be benign, actually has a hidden malicious purpose. Trojan horses either replace existing files with malicious versions or add new malicious files to hosts. They often deliver other attacker tools to hosts." [NIST](https://nvlpubs.nist.gov/nistpubs/specialpublications/nist.sp.800-83r1.pdf)


#### Worms
"A worm is a type of virus that can spread without human interaction. Worms often spread from computer to computer and take up valuable memory and network bandwidth, which can cause a computer to stop responding. Worms can also allow attackers to gain access to your computer remotely." [CISA.gov](https://www.cisa.gov/uscert/publications/virus-basics)

"A worm is a self-replicating, self-contained program that usually executes itself without user intervention." [NIST](https://nvlpubs.nist.gov/nistpubs/specialpublications/nist.sp.800-83r1.pdf)

Worms require no user interaction to spread or execute. Like a virus, they are not necessarily malicious. 

#### Virus
"A computer virus is a program that spreads by first infecting files or the system areas of a computer or network router's hard drive and then making copies of itself. Some viruses are harmless, others may damage data files, and some may destroy files." [CISA.gov](https://www.cisa.gov/uscert/publications/virus-basics)

Viruses require a human to "launch" them and a vulnerable environment (application or network) to "host" them. Not every virus is malicious.

The [Wikipedia article on viruses](https://en.wikipedia.org/wiki/Computer_virus) has a very controversial claim: There is no such thing as a benevolent virus. By the writer's logic, the benevolent behavior of the virus would be sought by the user and would not require stealth tactics to propagate.

#### Rootkits
Malware that obscures the execution of other malware. Adapted from *Malware Analysis and Detection Engineering*. 

"A rootkit is a collection of files that is installed on a host to alter its standard functionality in a malicious and stealthy way. A rootkit typically makes many changes to a host to hide the rootkit’s existence, making it very difficult to determine that the rootkit is present and to identify what the rootkit has changed." [NIST](https://nvlpubs.nist.gov/nistpubs/specialpublications/nist.sp.800-83r1.pdf)

#### Keyloggers (again, info stealing)
A keylogger is a kind of spyware that can log the user’s keystrokes and send the recorded keystrokes back to the attacker. *Malware Analysis and Detection Engineering*

See also _spyware (InfoStealers)_.

#### Bots
Similar to a backdoor, bots are malicious software that allows an attacker access to a system/network. Bots differ from backdoors because all computers infected with the same bot receive the same instructions from a single command-and-control server and operate in coordination to form a _botnet_. Adapted from *Practical Malware Analysis*

#### Mobile
"Mobile malware is malicious software specifically designed to target mobile devices, such as smartphones and tablets, with the goal of gaining access to private data." [Crowdstrike](https://www.crowdstrike.com/cybersecurity-101/malware/mobile-malware/)

Do you think that this deserves to be a special category?

#### Backdoors
"A backdoor is a malicious program that listens for commands on a certain TCP or UDP port. Most backdoors allow an attacker to perform a certain set of actions on a host, such as acquiring passwords or executing arbitrary commands." [NIST](https://nvlpubs.nist.gov/nistpubs/specialpublications/nist.sp.800-83r1.pdf)

See also _bots_.

#### Downloaders
A downloader is malware that downloads other malware. Botnets work as downloaders and download malware upon receiving a command from the central server. *Malware Analysis and Detection Engineering*

#### Cryptominers
A cryptominer is a relatively new type of malware, having become popular with the increasing use of cryptocurrencies. This malware is rarely known to steal data from the victim’s machine, but does cause wasted use of system resources by surreptitiously mining cryptocurrencies. Adapted from *Malware Analysis and Detection Engineering*
