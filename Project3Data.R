file <- 'Data/RAW_recipes.csv'

library(tidyverse)
library(purrr)
library(stringr)

#read in the file
recipes <- 
  read_csv(file,
           col_select = c("name", "minutes", "tags", "n_steps", "steps", "ingredients"))

#remove this line for final, UNCOMMENT for sample out
#recipes <- slice_head(recipes, n=20)

#tags that we will use for the final product
tagsToKeep <- c("60-minutes-or-less", "side-dishes", "mexican", "easy", "fall", 
                "holiday-event", "vegetarian", "winter", "30-minutes-or-less", 
                "breakfast", "main-dish", "kid-friendly", "15-minutes-or-less", 
                "desserts","no-cook", "indian", "asian", "north-american",
                 "vegan", "healthy", "seafood", "chicken","meat", "salads")

#get tags in the right format
recipes <- 
  recipes |>
  mutate(tags = str_sub(tags, 2, -2), 
         tags = str_replace_all(tags, "\\'", ""),
         tags = str_split(tags, ", "))
         #tags = str_replace_all(tags, ",", ""))
  
#get rid of the tags that arent the tags we want to keep
recipes <- 
  recipes |>
  mutate(tags = map(tags, ~ intersect(tagsToKeep, .x)))

#filter for only the recipes that have tags we want
recipes <-
  recipes |>
  filter(map_int(tags, length) != 0)

# Combine the tags back into a single character vector
recipes$tags <- map_chr(recipes$tags, toString)

recipes <- mutate(recipes, tags=str_replace_all(tags, ",", ""))

#get ingredients in the right format 
recipes <- 
  recipes |>
  mutate(ingredients = as.character(ingredients),
         ingredients = str_sub(ingredients, 2, -2), 
         ingredients = str_replace_all(ingredients, "\\'", ""),
         ingredients = str_split(ingredients, ", "))

# Combine the ingredients back into a single character vector
recipes$ingredients <- map_chr(recipes$ingredients, toString)


#get rid of the brackets on the steps
recipes <- 
  recipes |>
  mutate(steps = as.character(steps),
         steps = str_sub(steps, 2, -2))


# Iterate over each row of the 'steps' column
for (i in 1:nrow(recipes)) {
  # Split the string into individual steps
  steps <- str_split(recipes$steps[i], ", '")[[1]]
  
  # Add the step number before each step
  steps <- paste0(seq_along(steps), ". ", steps)
  
  # Combine the steps back into a single string and replace the original value
  #recipes$steps[i] <- paste(steps, collapse = "\n")
  recipes$steps[i] <- paste(steps, collapse = ". ")
}

#remove the ' 
recipes <- 
  recipes |>
  mutate(steps = str_replace_all(steps, "\\'", ""))

recipes$steps <- map_chr(recipes$steps, toString)
recipes$name <- map_chr(recipes$name, toString)
recipes$minutes <- map_chr(recipes$minutes, toString)
recipes$n_steps <- map_chr(recipes$n_steps, toString)

#write to file
write.csv(recipes, "FINAL_DATA.csv", row.names = FALSE, col.names= FALSE)
