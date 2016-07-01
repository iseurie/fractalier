#Fractalier

_Fractalier_ is a web service allowing users to more thoroughly explore fractals, 
leveraging the power of the cloud to offload the prohibitive demand of extremely 
high-resolution and precise custom renderings. There are three components of the 
implementation, these being the fractal rendering and calculation in the backend, and the 
clients, which will interface via RFC 6455 websocket protocol with the server-side 
implementation. Servers will pass generyation and rendering parameters, allowing clients to 
display the resulting bitmap to the user in a live feed. It will be supported by a freemium 
business model, likely with advertisements implemented client-side and perhaps a fee to 
allow users to waive them, or payments to unlock higher rendering resolution and precision.
