# Load the necessary packages
library(ggplot2)
library(dplyr)
library(lubridate)

# Read in the data
energy_data <- read.csv("energy_data.csv")

# Convert the date column to a datetime format
energy_data$date <- ymd_hms(energy_data$date)

# Aggregate the data by day to get the total energy consumption for each day
energy_by_day <- energy_data %>%
  mutate(day = as.Date(date)) %>%
  group_by(day) %>%
  summarise(total_energy = sum(energy_consumed))

# Create a plot of the total energy consumption by day
ggplot(data = energy_by_day, aes(x = day, y = total_energy)) +
  geom_line(color = "blue", size = 1.5) +
  geom_smooth(method = "lm", formula = y ~ x, color = "red", size = 1) +
  scale_x_date(date_labels = "%b %d", date_breaks = "1 day") +
  scale_y_continuous(limits = c(0, max(energy_by_day$total_energy) * 1.1), 
                     expand = c(0, 0.05)) +
  labs(x = "Date", y = "Total Energy Consumption", 
       title = "Daily Energy Consumption", 
       subtitle = "January - June 2022") +
  theme(plot.title = element_text(size = 22, face = "bold", color = "darkblue"),
        plot.subtitle = element_text(size = 18, color = "darkblue"),
        axis.title.x = element_text(size = 16, color = "darkblue"),
        axis.title.y = element_text(size = 16, color = "darkblue"),
        axis.text.x = element_text(size = 14, color = "darkblue"),
        axis.text.y = element_text(size = 14, color = "darkblue"),
        axis.line = element_line(color = "black", size = 1),
        panel.background = element_rect(fill = "lightgray", color = "gray", size = 1, 
                                        linetype = "solid"),
        panel.grid.major = element_line(color = "white", size = 0.5),
        panel.grid.minor = element_line(color = "white", size = 0.5),
        panel.border = element_rect(color = "gray", fill = NA, size = 1))
