import numpy as np

def step_euler(tau, state):
    state[0] += tau*state[1]
    state[1] += tau*state[2]
    return state

def step_euler_cromer(tau, state):
    state[1] += tau*state[2]
    state[0] += tau*state[1]
    return state

def step_midpoint(tau, state):
    v_last = np.array(state[1])
    state[1] += tau * state[2]
    state[0] += tau * 0.5 * (state[1] + v_last)
    return state
    
def step_verlet(tau, state_old, state):
    state_new = np.array(state)
    state_new[0] = 2*state[0] - state_old[0] + tau**2*state[2]
    state_new[1] = (state_new[0] - state_old[0])*0.5/tau
    state_new[2] = state[2]
    state_old[:] = state[:]
    state[:] = state_new[:]
    return state

def step_rk4(tau, state, flow):    
    F1 = tau * flow(state)    
    F2 = tau * flow(state + F1 * 0.5)
    F3 = tau * flow(state + F2 * 0.5)
    F4 = tau * flow(state + F3)
    state += (F1 + 2*F2 + 2*F3 + F4)/6.0
    return state
