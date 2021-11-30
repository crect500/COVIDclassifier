import PySimpleGUI as psg
from gui_funcs import *


if __name__ == '__main__':
    ###Main###
    
    
    #Allowable input values for each data section
    s_list = ['Male','Female']
    r_list = ['Hawaiian/Pacific Islander', 'White', 'Black', 'Asian', 'Hispanic/Latino', 'Native American/Alaskan Native']
    pre_list = ['Yes', 'No']


    #Window Layout
    layout=[[psg.Text('Sex',size=(20, 1), font='Lucida',justification='left')],
            [psg.Combo(s_list,default_value='Male',key='Sex')],
            
            [psg.Text('Race',size=(30, 1), font='Lucida',justification='left')],
            [psg.Combo(r_list,default_value='Hawaiian/Pacific Islander',key='Race')],
            
            [psg.Text('Pre-Existing Medical Condition',size=(30, 1), font='Lucida',justification='left')],
            [psg.Combo(pre_list,default_value='No',key='Condition')],
            
            [psg.Text('Age',size=(30, 1), font='Lucida',justification='left')],
            [psg.Slider(range=(1, 120), orientation='h', size=(20, 15), default_value=25,key='Age')],
                    
            [psg.Button('Submit', font=('Times New Roman',12)),psg.Button('Exit', font=('Times New Roman',12))]]



    #Window
    win = psg.Window('COVID-19 Risk Predictor',layout)


    #Read values entered by user
    while True:

        #Read the Window events, values
        event, value = win.read()
        
        #Close window if user chooses 'Exit'
        if event in ('Exit', psg.WIN_CLOSED):
            break
        
        #Error Check user input
        if not value_check(value):
            psg.popup('Invalid Input')
        else:
            #Calculate probability
            h = calc_h(value)
            z = calc_z(h)
            p = round(calc_p(z),4)
            
            #popup results
            psg.popup('Probability of Required Hospitalization:', str(p*100) + '%')



    win.close()


