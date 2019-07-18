class SaveButtons(wx.Panel):
    """SaveButtons in general page
    
    The design of the savebuttons.
    """
    def __init__(self, parent, ext_format="*", lbl2="Save",
                 lbl1="Save As", flags=wx.FD_SAVE|wx.FD_OVERWRITE_PROMPT):
        wx.Panel.__init__(self, parent)
        
        self._ext_format = ext_format
        self._flags = flags

        Sizer = wx.BoxSizer(wx.HORIZONTAL)
        
        self.text = wx.TextCtrl(self)
        self.save_as_button = wx.Button(self, -1, lbl1)
        self.save_button = wx.Button(self, -1, lbl2)

        Sizer.Add(self.text, 1, wx.RIGHT, 5)
        Sizer.Add(self.save_as_button, 0, wx.RIGHT, 5)
        Sizer.Add(self.save_button, 0, wx.RIGHT, 5)

        self.SetSizer(Sizer)

        self.save_button.Bind(wx.EVT_BUTTON, self.OnSave)
        self.save_as_button.Bind(wx.EVT_BUTTON, self.OnSaveAs)

    @getException
    def OnSave(self, event):
        if self.GetValue():
            event.Skip()
        else:
            self.OnSaveAs(event)

    @getException
    def OnSaveAs(self, event):
        path = os.path.split(self.GetValue())
        val = FileDialog(ext_format=self._ext_format,
                         flags=self._flags,
                         defaultDir=path[0], defaultFile=path[1])
        if val:
            self.SetValue(val)
            event.Skip()
        
    def GetValue(self):
        return self.text.GetValue()

    def SetValue(self, value):
        self.text.SetValue(value)

    def Clear(self):
        self.SetValue("")
