﻿

#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class SwapChainPanel;
                ref class Button;
                ref class Flyout;
                ref class Grid;
            }
        }
    }
}

namespace CocosAppWinRT
{
    partial ref class OpenGLESPage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::SwapChainPanel^ swapChainPanel;
        private: ::Windows::UI::Xaml::Controls::Button^ cocos2d_editbox;
        private: ::Windows::UI::Xaml::Controls::Flyout^ cocos2d_editbox_flyout;
        private: ::Windows::UI::Xaml::Controls::Grid^ cocos2d_editbox_grid;
        private: ::Windows::UI::Xaml::Controls::Button^ cocos2d_editbox_done;
        private: ::Windows::UI::Xaml::Controls::Button^ cocos2d_editbox_cancel;
    };
}
