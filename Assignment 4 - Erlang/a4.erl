-module(a4).
-export([cardealership/2, convertprice/2]).

main(_) -> io:fwrite(cardealership("BMW", "eur")).

cardealership(Car, Currency) ->
    CARS = #{ "BMW" => 15000, "FERRARI" => 17000, "FORD" => 20000 },
    CP = convertprice(maps:get(Car, CARS, -1), Currency),
    RoundedPrice = round(CP),
    io:fwrite("Price: " ++ integer_to_list(RoundedPrice) ++ "\n" ++ "If the price is negative, then the currency or car is wrong or does not exist\n").

convertprice(Price, Currency) ->
    case Currency of
        "eur" -> Price * 0.92;
        "inr" -> Price * 82.08;
        _ -> -1
    end.
