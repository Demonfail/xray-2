﻿#pragma checksum "..\..\..\property_grid_editors\Single_editor.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "CD5E60253303CE338187771B94AF384B"
//------------------------------------------------------------------------------
// <auto-generated>
//     Этот код создан программой.
//     Исполняемая версия:4.0.30319.42000
//
//     Изменения в этом файле могут привести к неправильной работе и будут потеряны в случае
//     повторной генерации кода.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms.Integration;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using xray.editor.wpf_controls.converters;


namespace xray.editor.wpf_controls.property_grid_editors {
    
    
    /// <summary>
    /// Single_editor
    /// </summary>
    public partial class Single_editor : System.Windows.Controls.UserControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 10 "..\..\..\property_grid_editors\Single_editor.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ProgressBar progress_bar;
        
        #line default
        #line hidden
        
        
        #line 14 "..\..\..\property_grid_editors\Single_editor.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox text_box;
        
        #line default
        #line hidden
        
        
        #line 24 "..\..\..\property_grid_editors\Single_editor.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ToolTip EditorToolTip;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/wpf_controls;component/property_grid_editors/single_editor.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\property_grid_editors\Single_editor.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.progress_bar = ((System.Windows.Controls.ProgressBar)(target));
            return;
            case 2:
            this.text_box = ((System.Windows.Controls.TextBox)(target));
            
            #line 17 "..\..\..\property_grid_editors\Single_editor.xaml"
            this.text_box.PreviewMouseDoubleClick += new System.Windows.Input.MouseButtonEventHandler(this.text_box_PreviewMouseDoubleClick);
            
            #line default
            #line hidden
            
            #line 18 "..\..\..\property_grid_editors\Single_editor.xaml"
            this.text_box.PreviewMouseLeftButtonDown += new System.Windows.Input.MouseButtonEventHandler(this.TextBox_PreviewMouseLeftButtonDown);
            
            #line default
            #line hidden
            
            #line 19 "..\..\..\property_grid_editors\Single_editor.xaml"
            this.text_box.PreviewMouseMove += new System.Windows.Input.MouseEventHandler(this.TextBox_PreviewMouseMove);
            
            #line default
            #line hidden
            
            #line 20 "..\..\..\property_grid_editors\Single_editor.xaml"
            this.text_box.AddHandler(System.Windows.Controls.Validation.ErrorEvent, new System.EventHandler<System.Windows.Controls.ValidationErrorEventArgs>(this.TextBox_Error));
            
            #line default
            #line hidden
            return;
            case 3:
            this.EditorToolTip = ((System.Windows.Controls.ToolTip)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

