# Parser
* Created the project to learn how to build a continuous integration framework with Jenkins and GitHub.
* This application has a client and server - the client sends CSV data to the server which parses 
it and stores it in SQLite database. 
* Tested the client code using Boost Unit Test Framework and the server code with Google Test Framework.
* When there are changes in the GitHub repository, GitHub sends a HTTP POST message to the configured 
Jenkins server using webhooks. (URL is provided by ngrok - see below).

![Alt test](https://github.com/arjunagi/Parser/blob/master/Screenshots/GitHub_Webhooks.png)

![Alt test](https://github.com/arjunagi/Parser/blob/master/Screenshots/GitHub_Push.png?raw=true "Git push log")

* When Jenkins receives this HTTP POST message from GitHub, it starts to build the project and also runs the testcases.

![Alt test](https://github.com/arjunagi/Parser/blob/master/Screenshots/ProjectInfo_With_TestResults.png?raw=true "Build and test results")

![Alt test](https://github.com/arjunagi/Parser/blob/master/Screenshots/TestResults.png?raw=true)

* As the Jenkins server was running on localhost, I used the ngrok tool (https://ngrok.com/) to
provide a tunnel for GitHub to reach my localhost.

![Alt test](https://github.com/arjunagi/Parser/blob/master/Screenshots/ngrok.png)
