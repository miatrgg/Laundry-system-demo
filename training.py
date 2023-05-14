# import libraries
import pandas as pd
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

# read in data from CSV file
data = pd.read_csv('laundry_data.csv')

# separate target variable and input variables
X = data.drop(['Energy Consumption'], axis=1)
y = data['Energy Consumption']

# split data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# create instance of decision tree regression model
model = DecisionTreeRegressor(random_state=42)

# fit model to training data
model.fit(X_train, y_train)

# make predictions on test data
y_pred = model.predict(X_test)

# calculate root mean squared error of model predictions
rmse = mean_squared_error(y_test, y_pred, squared=False)
print('Root Mean Squared Error:', rmse)

# example usage of model to predict energy consumption for a new laundry load
new_load = [[7.0, 5, 40, 1]]
predicted_energy = model.predict(new_load)
print('Predicted Energy Consumption:', predicted_energy)
