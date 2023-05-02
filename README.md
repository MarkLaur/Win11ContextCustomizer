# Win11ContextCustomizer
A Windows 11 app that enables users to add custom elements to the right click menu.
Windows 11's new right click menu can't be edited with a simple registry tweak. Instead, installed apps implement a thingy with the windows api and kindly request windows to add elements to the menu. This means that even power users can't edit the menu. This is where my app comes in.

This will be built into a signed MSIX package. Initially it'll be a self-signed one, requiring the user to install the root certificate.

# Features and limitations
The API has some limitations, such as forcing all right elements of a single program under the same "folder". Access to the menu is also limited to signed packages.

This app will allow the user to add customized elements to the right click menu. The user will be able to customize the element count, along with elements' titles, icons and effects. I don't yet know exactly what can be accessed through the api but a simple console command should be possible, enabling the user to do almost anything.

Editing or removing existing elements is out of scope and possibly impossible.
