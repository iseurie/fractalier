#Fractalier
----

_Fractalier_ is a web service allowing users to more thoroughly explore fractals 
and employ more artistic license in creating custom renders of fractals by 
leveraging the power of the cloud. There are three components of the 
implementation, these being the rendering and generation (in the backend), which 
will interface via RFC 6455 websocket protocol with clients, which will pass 
generation and rendering parameters and display the resulting bitmap to the user in 
a live feed.
