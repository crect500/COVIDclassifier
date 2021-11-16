import PySimpleGUI as psg




#Layout
layout=[[psg.Text('Sex',size=(20, 1), font='Lucida',justification='left')],
        [psg.Combo(['Male','Female'],default_value='Male',key='Sex')],
        
        [psg.Text('Race',size=(30, 1), font='Lucida',justification='left')],
        [psg.Combo(['Hawaiian/Pacific Islander', 'White', 'Black', 'Asian', 'Hispanic/Latino', 'Native American/Alaskan Native'],default_value='Hawaiian/Pacific Islander',key='Race')],
        
        [psg.Text('Pre-Existing Medical Condition',size=(30, 1), font='Lucida',justification='left')],
        [psg.Combo(['Yes', 'No'],default_value='No',key='Condition')],
        
        [psg.Text('Age',size=(30, 1), font='Lucida',justification='left')],
        [psg.Slider(range=(1, 120), orientation='h', size=(20, 15), default_value=25,key='Age')],
                
        [psg.Button('Submit', font=('Times New Roman',12)),psg.Button('Exit', font=('Times New Roman',12))]]
#Window
win = psg.Window('COVID-19 Risk Predictor',layout)

#Read values entered by user
while True:
    # Read the Window
    event, value = win.read()
    if event in ('Exit', psg.WIN_CLOSED):
        break
    """
    *
    **
    ***
    Insert witchcraft here to communicate with Machine
    ret results
    ***
    **
    *
    """
    
    #popup results
    psg.popup('Results',
            'Something results.',
            'The button clicked was "{}"'.format(event),
            'Here are ye ol values', value)



win.close()


