import numpy as np
from numpy.lib.stride_tricks import sliding_window_view

def getNextState(state):
    """
    @param state: 2d array of 0 and 1 where 0 represents a dead cell and 1 represents a live cell
    @return: 2d array of 0 and 1 computed from the input state
    """
    
    state = np.array(state)
    
    h,w = state.shape
    padding = np.hstack((np.zeros((h,1)),state,np.zeros((h,1))))
    padding = np.vstack((np.zeros((1,w+2)),padding,np.zeros((1,w+2))))
    
    # n: numpy array that has the same shape as the input state
    # each cell represents the number of live neighbours
    n = sliding_window_view(padding,(3,3)).sum(axis=(2,3)) - state

    # rules according to Wikipedia:
    # any live cell with 2 or 3 neighbours survives
    # any dead cell with 3 live neighbours becomes a live cell
    # all other live or dead cells die in the next generation
    return np.where(((state==1)&((n==2)|(n==3)))|((state==0)&(n==3)),1,0).tolist()
