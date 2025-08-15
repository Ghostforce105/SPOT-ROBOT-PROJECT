import pandas as pd
from sklearn.tree import DecisionTreeClassifier
import joblib
import csv

data = pd.read_csv(real_dataset.csv)

df = pd.DataFrame(data)


X = df[['time_of_day', 'task_priority', 'room_dirt_level']]
y = df['room_name']


model = DecisionTreeClassifier()
model.fit(X, y)

# Save model
joblib.dump(model, 'room_decision_model.joblib')
print("Model trained and saved as room_decision_model.joblib")
