## Text Scaling
There is a font texture atlas that can be rebuilt with different configurations. To change the size of the default font you can do this:
```c++
float FONT_SCALE = 2.5f;
ImFontConfig config;
config.SizePixels = 13 * FONT_SCALE;
auto imguiIO = ImGui::GetIO();
auto font = igIO.Fonts->AddFontDefault(&config);
```

You can also use `ImGui::PushFont()` and `ImGui::PopFont()` to switch between fonts that you've stored.

## Tables
```c++
// [Method 1] Using TableNextRow() to create a new row, and TableSetColumnIndex() to select the column.
// In many situations, this is the most flexible and easy to use pattern.
if (ImGui::BeginTable("table1", 3))
{
    for (int row = 0; row < 4; row++)
    {
        ImGui::TableNextRow();
        for (int column = 0; column < 3; column++)
        {
            ImGui::TableSetColumnIndex(column);
            ImGui::Text("Row %d Column %d", row, column);
        }
    }
    ImGui::EndTable();
}
```

#### Customization
##### Borders
`ImGuiTableFlags_BordersOuter` - Outside lines of table
`ImGuiTableFlags_BordersInnerV` - Inner vertical lines of table

##### Table Dimensions
Row height:
`ImGui::TableNextRow(ImGuiTableRowFlags_None, min_row_height)`

Explicitly set the table dimensions
`ImGui::TableNextRow(ImGuiTableRowFlags_None, min_row_height)`
`ImGuiTableFlags_SizingFixedSame`

# Application
### Board Style
- Font = 50.f
- maxTableSize = (595.f, 0.f)
- Cell Padding = (13.f, 0.f)
- minimumCellSize = 0.f;
- Table Flags
	- ImGuiTableFlags_Borders
- Line thickness (colour instead)
- Gonna need a text buffer set for each tile (81 chars + '\\0')
### Text field style/behaviour
