import math

#Allowable input values for each data section
s_list = ['Male','Female']
r_list = ['Hawaiian/Pacific Islander', 'White', 'Black', 'Asian', 'Hispanic/Latino', 'Native American/Alaskan Native']
pre_list = ['Yes', 'No']



def value_check(d):
    """
    Check values input by the GUI against acceptable values in the lists.

    Arguments:
    ----------
    d - Dictionary comprised of inputs from win.read() (using PySimpleGUI)

    Returns:
    --------
    boolean
    """
    for key in d:
        if key == 'Sex':
            if d[key] not in s_list:
                return False
        elif key == 'Race':
            if d[key] not in r_list:
                return False
        elif key == 'Condition':
            if d[key] not in pre_list:
                return False
                
    return True



def calc_h(d):
    """
    Calculates value of h(x) using results from Binary classifier and user input data.

    Arguments:
    ----------
    d - Dictionary comprised of inputs from win.read() (using PySimpleGUI)

    Returns:
    --------
    h - calculated value
    """
    h = 0.3028*math.exp(0.03*int(d['Age']))
    
    if d['Sex'] == 'Male':
        h = h - 2.1861
    else:
        h = h - 2.5518
        
    if d['Race'] == 'Hawaiian/Pacific Islander':
        h = h - 0.4612
    elif d['Race'] == 'White':
        h = h - 2.5132
    elif d['Race'] == 'Black':
        h = h - 1.4031
    elif d['Race'] == 'Asian':
        h = h - 1.5652
    elif d['Race'] == 'Hispanic/Latino':
        h = h - 1.5934
    else:
        h = h + 0.5180
        
    if d['Condition'] == 'Yes':
        h = h + 1.3101
        
    return h



def calc_z(h):
    """
    Calculates value of z(h) as:

        z(h) = exp[-h(x)]

    Arguments:
    ----------
    h - Value calculated from Binary classifier

    Returns:
    --------
    z - calculated value
    """
    return math.exp(-h)
    
    
    
def calc_p(z):
    """
    Calculates probability p:

        p(h) = 1/(1+z)

    Arguments:
    ----------
    z - calculated z(h) value

    Returns:
    --------
    p - calculated value
    """
    return 1/(1+z)

