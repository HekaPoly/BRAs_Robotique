import numpy as np
import sympy as sp
import matplotlib.pyplot as plt
from time import *

def Affichage_configuration(t1,t2,t3,t4,t5,T01,T12,T23,T34,T45,l1,l2,l3,l4):

    T01_eval = T01.subs([(theta1,t1),
                         (L1,l1)])
    T12_eval = T12.subs([(theta2,t2)])
    T23_eval = T23.subs([(theta3,t3),
                         (L2,l2)])
    T34_eval = T34.subs([(theta4,t4),
                         (L3,l3)])
    T45_eval = T45.subs([(theta5,t5)])

    T05_eval = T01_eval*T12_eval*T23_eval*T34_eval*T45_eval
    coord_O = [0,0,0]
    coord_A = [0,0,l1]
    
    coord_B = (T01_eval*T12_eval)*sp.Matrix([0,l2,0,1])
    coord_B = coord_B[0:3]

    coord_C = (T01_eval*T12_eval*T23_eval)*sp.Matrix([0,l3,0,1])
    coord_C = coord_C[0:3]

    coord_D = T05_eval*sp.Matrix([0,l4,0,1])
    coord_D = coord_D[0:3]

    Segment_OA = [[coord_O[0],coord_A[0]],[coord_O[1],coord_A[1]],[coord_O[2],coord_A[2]]]
    Segment_AB = [[coord_A[0],coord_B[0]],[coord_A[1],coord_B[1]],[coord_A[2],coord_B[2]]]
    Segment_BC = [[coord_B[0],coord_C[0]],[coord_B[1],coord_C[1]],[coord_B[2],coord_C[2]]]
    Segment_CD = [[coord_C[0],coord_D[0]],[coord_C[1],coord_D[1]],[coord_C[2],coord_D[2]]]

    fig = plt.figure()
    ax = plt.axes(projection='3d')
    ax.set_title('Configuration du robot')
    ax.set_xlabel('Axe X')
    ax.set_ylabel('Axe Y')
    ax.set_zlabel('Axe Z')
    ax.plot(Segment_OA[0], Segment_OA[1], Segment_OA[2], 'red')
    ax.plot(Segment_AB[0], Segment_AB[1], Segment_AB[2], 'green')
    ax.plot(Segment_BC[0], Segment_BC[1], Segment_BC[2], 'orange')
    ax.plot(Segment_CD[0], Segment_CD[1], Segment_CD[2], 'purple')
    plt.show()



theta1,theta2,theta3,theta4,theta5,L1,L2,L3,L4 = sp.symbols('theta1,theta2,theta3,theta4,theta5,L1,L2,L3,L4',positive=True)


# Generation des matrices de transformations rigides par la methode de deplacements succesifs

T01 = sp.Matrix([[sp.cos(theta1),-sp.sin(theta1),0,0 ],     """ Cette matrice exprime la pose du repere 0 exprimee dans le repere 1. Cela provient  """
                 [sp.sin(theta1), sp.cos(theta1),0,0 ],     """ d'une combinaison d'une rotation du repere 1 autour de l'axe z d'un angle theta 1   """
                 [       0      ,         0     ,1,L1],     """ et d'une translation du repere 0 d'une longueur L1 le long de l'axe z.              """
                 [       0      ,         0     ,0, 1]])                     

T12 = sp.Matrix([[1,             0,              0,0],      """ Cette matrice exprime la pose du repere 1 exprimee dans le repere 2. Cela provient  """
                 [0,sp.cos(theta2),-sp.sin(theta2),0],      """ d'une rotation du repere 1 autour de l'axe x d'un angle theta 2                     """
                 [0,sp.sin(theta2), sp.cos(theta2),0],      
                 [0,             0,              0,1]])

T23 = sp.Matrix([[1,             0,              0,0 ],     """ Cette matrice exprime la pose du repere 2 exprimee dans le repere 3. Cela provient """
                 [0,sp.cos(theta3),-sp.sin(theta3),L2],     """ d'une combinaison d'une rotation du repere 2 autour de l'axe x d'un angle theta 3  """
                 [0,sp.sin(theta3), sp.cos(theta3),0],      """ et d'une translation du repere 2 d'une longueur L2 le long de l'axe y.             """
                 [0,             0,             0,1]])

T34 = sp.Matrix([[ sp.cos(theta4),0,sp.sin(theta4), 0],     """ Cette matrice exprime la pose du repere 3 exprimee dans le repere 4. Cela provient d'une """
                 [       0       ,1,      0       ,L3],     """ combinaison d'une rotation du repere 3 autour de l'axe y d'un angle theta 4 et           """
                 [-sp.sin(theta4),0,sp.cos(theta4), 0],     """ d'une translation du repere 3 vers le repere 5 d'une longueur L3 le long de l'axe y.     """
                 [       0       ,0,      0       , 1]])
T45 = sp.Matrix([[1,             0,              0,0],      """ Cette matrice exprime la pose du repere 4 exprimee dans le repere 5. Cela provient  """
                 [0,sp.cos(theta5),-sp.sin(theta5),0],      """ d'une rotation du repere 4 autour de l'axe x d'un angle theta 5                     """
                 [0,sp.sin(theta5), sp.cos(theta5),0],
                 [0,             0,              0,1]])

T05 = T01*T12*T23*T34*T45,                                   """ Cela illustre la pose final du robot dans son espace de configuration."""

p_final = T05[0:3,3]
R05 = T01[0:3,0:3]*T12[0:3,0:3]*T23[0:3,0:3]*T34[0:3,0:3]*T45[0:3,0:3]      

Affichage_configuration(0,0,0,0,0,                          
                        T01,T12,T23,T34,T45,
                        50,150,150,50) ;                      """ Affichage 3D de la maquette du robot dans sa position de repos"""





















