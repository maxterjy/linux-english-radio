# VOA Learning English

## Summary
A Linux CLI application to practice English listening based on VOA API  
https://learningenglish.voanews.com/podcasts  
  
Features
* Fetch channel, news list from podcasts  
* Audio player   

## Screencast
<div align="center">
  <a href="https://www.youtube.com/watch?v=eqAWmTActIw"><img src="https://github.com/maxterjy/voa-learning-english-linux/blob/master/screenshot/Screenshot%20from%202019-12-06%2019-36-10.png" width="256" alt=""></a>
</div>

Youtube: https://youtu.be/eqAWmTActIw

## Development
### Dependency
The project is written in C++ and using the following libaries:
* Gstreamer 1.0 to implement audio player
* CURL, TinyXML2 to implement news pullers
* C Pthreads to perform UI and background task at the same time

### Building
Install dependency  
`./install-dependency.sh`

Build  
`make`

Run  
`./app`
