   M S B A M L   `   `   `  ���� G  Cwpf_controls, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullC&clr-namespace:xray.editor.wpf_controlsxray.editor.wpf_controls  L    Fxray.editor.wpf_controls.property_grid_item_editors.common_item_editor   \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     8x,http://schemas.microsoft.com/winfx/2006/xaml    6local&clr-namespace:xray.editor.wpf_controls      � 	Resources  8  2xray.editor.wpf_controls.editor_selector_extractor   editor_selector_extracterE  ?xray.editor.wpf_controls.property_grid_empty_collection_checher  empty_collection_checher;  5xray.editor.wpf_controls.bool_to_visibility_converter ) %bool_to_collapse_visibility_converter   need_to_hide % !bool_to_hide_visibility_converter   need_to_reverse 2 .bool_to_collapse_visibility_converter_reverced��%Y   &	        &	      &	 
     &	      &	               .    . .����  J� SnapsToDevicePixels . .+��� #��Z�$��
0, 0, 0, 1q� . ._�� $��18�� .  � ColumnDefinitions �� $��16 ��� $
��Auto � z� SharedSizeGroup$ PropertyName���� $��3 ��� $��* �.+��� $��0��$��0q�#��Z�._�� $��
0, 0, 1, 0q�y��� *is_expandable_item+ �� 	Converter# [ .+��� -   $��expand��$��11��$��11��.��� .+��� 	 �� X2$ 5��	 �� Y1$	 2.5��		 �� Y2$		 2.5��$��1��
���   �	
 �� X1$
 0�� . �� $	 2.5��$	
 2.5��$ 0��$	 5��$��1��
���   � . �� -   $��collapse��$��11��$��11��$y�	Collapsed=�.��� .+��� $ 5��$ 2��$	 2��$��1��
���   �$
 0�� . �� $��1��#��Z�$��0q� �� Padding$ 
3, 0, 5, 0q�._��� -   $��item_text_panel�� �� Orientation$ 
Horizontal=�.+��� ����  �� Path$&  (local:property_grid.ItemIndent)� �� ElementName$ item_text_panel���� $��Center=����� *name+�� $��2��$��Stretch=�$��Center=�#��Z����� .R��� 
�������$��3��$��
1, 0, 1, 0q� . #��Z��� $��3��
�������$��0q�$ 
5, 0, 2, 0q�._�]� .+�� $��Right=�$��11��y��� *is_collection_item+# [ .+��� -   $��delete_item��$��11��$��11�� � ToolTip$ Delete this item��.��� .+��� $ 5��$ 2��$	 2��$��1��
���   �$
 0�� . �� ���� ���� # [   �� RelativeSource �� *FindAncestor+ �� AncestorType,   &xray.editor.wpf_controls.property_grid"  �� -   $��inner_data_border��
�������$��0q� . $y�	Collapsed=�._�� .+��� -   $��	sub_items��$��0q�   
ItemIndent �� $&  (local:property_grid.ItemIndent)�$ inner_data_border��   item_indent_increaser# Z �� $��18��$��collection is empty��y��� *
HasItems+$ 	sub_items��# [ 