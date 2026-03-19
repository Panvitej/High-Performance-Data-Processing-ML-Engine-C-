// 1. Scale data
StandardScaler scaler;
scaler.fit(X);
auto X_scaled = scaler.transform(X);

// 2. Train model
AdvancedLinearRegression model(X[0].size());
model.fit(X_scaled, y);

// 3. Predict
auto preds = model.predict(X_scaled);

// 4. Evaluate
double error = Metrics::mse(y, preds);
double score = Metrics::r2(y, preds);
