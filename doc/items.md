# Items

**Widgets:**
- [Panel](#Panel)
- [Text](#Text)
- [Button](#Button)
- [Checkbox](#Checkbox)

**Other:**
- [Container](#Container)

---
## Panel
### Description:
The panel is equal to ```ImGui::BeginWindow()``` and ```ImGui::EndWindow()```.
Each widget must be created inside a panel.
### Attributes:
| Name | Type | Description | Default Value |
| --- | --- | --- | --- |
| position | Float2 | The start position of the panel, relative to the window.| (0, 0) |
| size | Float2 | The start size of the panel. | (0, 0) - Dynamic size based on the panel's child items. |
| title | String | The title of the panel | "##<item_address>", which is displayed as an empty string. |
### Implemented API functions:
| Function | Description |
| --- | --- |
| ```bool IsItemPressed()``` | Returns true if the panel or any of its child items is pressed by the user. |
| ```bool IsItemHovered()``` | Returns true if the Panel or any of its child items is hovered by the user. |
### Example:
```
// example.igm:

Panel
{
    title    = "Example panel"
    position = (300, 300)
    size     = (400, 100)

    Text { text = "This is a text inside the panel" }
}
```
![ExampleImage](img/items/panel.png)

---
## Text
### Description:
The text is equal to ```ImGui::Text()``` and is used to display basic information.
### Attributes:
| Name | Type | Description | Default Value |
| ---| --- | --- | --- |
| text | String | The text that will be displayed. | "" |
### Implemented API functions:
| Function | Description |
| --- | --- |
| ```bool IsItemPressed()``` | Returns true if the Text is pressed by the user. |
| ```bool IsItemHovered()``` | Returns true if the Text is hovered by the user. |
### Example:
```
// example.igm:

Panel
{
    title    = "Example panel"
    position = (300, 300)
    size     = (250, 200)

    Text { text = "Information 1" }
    Text { text = "Information 2" }
}
```
![ExampleImage](img/items/text.png)

---
## Button
### Description:
The button is equal to ```ImGui::Button()```.
### Attributes:
| Name | Type | Description | Default Value |
| --- | --- | --- | --- |
| text | String | The text that is displayed inside the button. | "" |
| size | Float2 | Size of the button | Size of the button contents. |
### Implemented API functions:
| Function | Description |
| --- | --- |
| ```bool IsItemPressed()``` | Returns true if the button is pressed by the user. |
| ```bool IsItemHovered()``` | Returns true if the button is hovered by the user. |
### Example:
```
// example.igm:

Panel
{
    title    = "Example panel"

    Button : button_0
    {
        text = "Press me"
    }

    Button : button_1
    {
        text = "Press me"
        size = (100, 20)
    }
}
```
```cpp
// example.cpp
if (gui::IsItemPressed(unit, "button_0"))
    std::cout << "button_0 is pressed" << std::endl;

if (gui::IsItemHovered(unit, "button_1"))
    std::cout << "button_1 is pressed" << std::endl;
```
![ExampleImage](img/items/button.png)

---
## Checkbox
### Description:
The checkbox is equal to ```ImGui::Checkbox()```.
### Attributes:
| Name | Type | Description | Default Value |
| ---| --- | --- | --- |
| text | String | Text that is displayed next to the checkbox. | "" |
| checked | Bool | Sets the state of the checkbox on startup. | False |
### Implemented API functions:
| Function | Description |
| --- | --- |
| ```bool IsItemPressed()``` | Returns true if the checkbox or its text is pressed by the user. |
| ```bool IsItemHovered()``` | Returns true if the checkbox or its text is hovered by the user. |
| ```bool IsCheckboxChecked()``` | Returns the state of the checkbox. |
### Example:
```
// example.igm:

Panel
{
    title    = "Example panel"
    position = (300, 300)
    size     = (150, 100)

    Checkbox : checkbox_0 { text = "checkbox 1" }

    Checkbox : checkbox_1
    {
        text = "checkbox 2"
        checked = true
    }
}
```
```cpp
// example.cpp
if (gui::IsCheckboxChecked(file, "checkbox_0"))
    std::cout << "checkbox_0 is checked" << std::endl;

if (gui::IsCheckboxChecked(file, "checkbox_1"))
    std::cout << "checkbox_1 is checked" << std::endl;
```
![ExampleImage](img/items/checkbox.png)

---
## Container
### Description:
The container is used to store custom data or to create namespaces.
### Attributes:
*The container currently does not have any attributes*
### Example:
```
// example.igm:

Container : container_0
{
    +string value_0 = "Value 0"
    +string value_1 = "Value 1"
    +string value_2 = "Value 2"
}

Panel
{
    title = "Example panel"

    Text { text = container_0.value_0  }  // Copy by value
    Text { text = container_0.value_1  }  // Copy by value
    Text { text = @container_0.value_2 }  // Copy by reference
}
```
![ExampleImage](img/items/container.png)
