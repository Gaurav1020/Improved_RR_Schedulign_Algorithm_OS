import os
import pandas as pd
import plotly.graph_objects as go
import plotly.express as px
import os.path
from os import path
patha=os.getcwd()
print(patha)
path_txt=patha+"\data.txt"
path_csv=patha+"\data.csv"
# with open(path+'\data.txt', 'r') as f:
#     print(f.read())
if(os.path.isfile(path_txt)):
    os.rename(path_txt,path_csv)

df=pd.read_csv(path_csv)
RR=df[df["Group"]=="RR"]
IRR=df[df["Group"]=="IRR"]
print(RR)
print(IRR)


fig = px.scatter(df
                , x='PID'
                , y='CT'
                , color='Group'
                , trendline='lowess'
                )
fig.update_layout(
    title="Completion Time",
    xaxis_title="PID",
    yaxis_title="Completion Time"
)
fig.update_traces(marker=dict(size=1.5))
if(os.path.isfile(patha+"\\CT.html")):
    os.remove(patha+"\\CT.html")
fig.write_html(patha+"\\CT.html")


fig1 = px.scatter(df
                , x='PID'
                , y='TAT'
                , color='Group'
                , trendline='lowess'
                )
fig1.update_layout(
    title="Turnaround Time",
    xaxis_title="PID",
    yaxis_title="Turnaround Time"
)
fig1.update_traces(marker=dict(size=1.5))
if(os.path.isfile(patha+"\\TAT.html")):
    os.remove(patha+"\\TAT.html")
fig1.write_html(patha+"\\TAT.html")


fig2 = px.scatter(df
                , x='PID'
                , y='WT'
                , color='Group'
                , trendline='lowess'
                )
fig2.update_layout(
    title="Waiting Time",
    xaxis_title="PID",
    yaxis_title="Waiting Time"
)
fig2.update_traces(marker=dict(size=1.5))
if(os.path.isfile(patha+"\\WT.html")):
    os.remove(patha+"\\WT.html")
fig2.write_html(patha+"\\WT.html")


rr_avgtat=[]
irr_avgtat=[]
rr_avgwt=[]
irr_avgwt=[]
rr_avgtat.append(RR['TAT'].mean())
rr_avgwt.append(RR['WT'].mean())
irr_avgtat.append(IRR['TAT'].mean())
irr_avgwt.append(IRR['WT'].mean())


fig3 = go.Figure(data=[
    go.Bar(x=pd.Series(RR['Group']).unique(), y=rr_avgtat),
    go.Bar(x=pd.Series(IRR['Group']).unique(), y=irr_avgtat)
])
fig3.update_layout(
    title="Average Turnaround Time",
    xaxis_title="Group",
    yaxis_title="Average Turnaround Time"
)
if(os.path.isfile(patha+"\\avgTAT.html")):
    os.remove(patha+"\\avgTAT.html")
fig3.write_html(patha+"\\avgTAT.html")


fig4 = go.Figure(data=[
    go.Bar(x=pd.Series(RR['Group']).unique(), y=rr_avgwt),
    go.Bar(x=pd.Series(IRR['Group']).unique(), y=irr_avgwt)
])
fig4.update_layout(
    title="Average Waiting Time",
    xaxis_title="Group",
    yaxis_title="Average Waiting Time"
)
if(os.path.isfile(patha+"\\avgWT.html")):
    os.remove(patha+"\\avgWT.html")
fig4.write_html(patha+"\\avgWT.html")


if(os.path.isfile(path_csv)):
    os.rename(path_csv,path_txt)

choice=input("Clear data for fresh use next time? (y/n): ")
if(choice=='y'):
    if(os.path.isfile(path_txt)):
        os.remove(path_txt)
    if(os.path.isfile(path_csv)):
        os.remove(path_csv)
    with open(path_txt, 'w') as fp:
        fp.write("Group,PID,AT,BT,CT,TAT,WT")
    print("Data deleted")
