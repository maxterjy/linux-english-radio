# VOA Learning English

## Summary
A Linux CLI application to practice English listening based on VOA API  
https://learningenglish.voanews.com/podcasts  
  
Features
* Fetch channel, news list from podcasts  
* Audio player   

## Screencast
<div align="center">
  <a href="https://youtu.be/j6MoS8k8K1Y"><img src="https://github.com/maxterjy/voa-learning-english-linux/blob/master/screenshot/screenshot.png" width="512" alt=""></a>
</div>

Youtube: https://youtu.be/j6MoS8k8K1Y

## Development
### Dependency
The project is written in C++ and using the following libaries:
* Gstreamer 1.0 to implement audio player
* CURL, TinyXML2 to implement news pullers
* C Pthreads to run UI and background task concurrently

### Building
Install dependency  
`./install-dependency.sh`

Build  
`make`

Run  
`./app`
