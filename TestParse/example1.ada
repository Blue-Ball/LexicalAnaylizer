--
-- Function using variable-sized array parameter.
--
with Gnat.Io; use Gnat.Io;
procedure f3 is
   -- A procedure which requires only input parameters.  It prints the
   -- indicated string the indicated number of times.
   procedure Print_Lots(S: String; N: Integer) is
      I : Integer;
   begin
      for I in 1..N loop
         Put(S);
      end loop;
   end Print_Lots;

   -- This requires an input and an output parameter.  It fills an
   -- existing String with a sequence of chacters starting with the
   -- one indicated.  Note that we have stated the in designation
   -- of Ch explicitly.  It is the default, so we did not need to state
   -- it.
   procedure Fill_String(S: out String; Chin: in Character) is
      I: Integer;               -- Loop index.
      Ch: Character := Chin;    -- Note: We cannot just use Chin, since it
                                -- is an input parameter, which we may not
                                -- change.
   begin
      for I in S'Range loop
         S(I) := Ch;
         Ch := Character'Succ(Ch);
         -- *** Chin := Character'Succ(Chin); *** -- Would not compile. --
      end loop;
   end Fill_String;

   -- This requires an in-out parameter.  It reverses the contents of
   -- a string.
   procedure Str_Rev(S: in out String) is
      Lower, Higher: Integer;   -- The lower and upper point in the swap scan.
      Tmp: Character;           -- Exchange temp.
   begin
      Higher := S'Last;
      for Lower in S'First .. (S'First + S'Last) / 2 loop
         -- Swap.
         Tmp := S(Lower);
         S(Lower) := S(Higher);
         S(Higher) := Tmp;

         -- Next pair
         Higher := Higher - 1;
      end loop;
   end Str_Rev;

   -- Some test strings.
   A: String(1..26);
   B: String(5..15);
begin
   Print_Lots("Hi ", 5);
   New_Line;

   Fill_String(A, 'A');
   Put_Line("Can you say your alphabet, Ada? " & A);

   Fill_String(B, '!');
   Put_Line("What you think of the rule against changing input parms? " & B);

   Str_Rev(B);
   Put_Line("What was that again? " & B);

   Str_Rev(A);
   Put_Line("Now say your zedy, Ada. " & A);
end f3;