# Win11ContextCustomizer
A Windows 11 app that enables users to add custom elements to the right click menu

This will be built into a signed MSIX package. Initially it'll be a self-signed one, requiring the user to install the root certificate. 

# Features and limitations
Windows 11's new right click menu can't be edited with a simple registry tweak. Instead, installed apps implement a thingy with the windows api. The API has some limitations, such as forcing all right click elements of a single app under an 
