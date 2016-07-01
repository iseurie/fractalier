#Fractalier

_Fractalier_ is a web service allowing users to more thoroughly explore fractals and employ 
more artistic license and depth in creating custom renders of fractals, leveraging the 
power of the cloud. There are three components of the implementation, these being the 
fractal rendering and calculation in the backend, and the clients, which will interface via 
RFC 6455 websocket protocol with the server-side implementation. Servers will pass 
generyation and rendering parameters, allowing clients to display the resulting bitmap to 
the user in a live feed.
